
#include "y/chemical/plexus/conservation/judge.hpp"
#include "y/mkl/tao/3.hpp"
#include "y/apex/simplify.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Broken:: ~Broken() noexcept
            {
            }

            Broken:: Broken(const Law & _law, const xreal_t _xs) noexcept :
            law(_law),
            xs(_xs)
            {
            }


            Broken:: Broken(const Broken &_) noexcept :
            law(_.law),
            xs(_.xs)
            {
            }

            bool Broken:: still(XAdd &xadd, const XReadable &Ctop)
            {
                xs = law.excess(xadd,Ctop,TopLevel);
                return xs.mantissa > 0;
            }


            std::ostream & operator<<(std::ostream &os, const Broken &broken)
            {
                os << std::setw(22) << broken.xs.str() << " @" << broken.law;
                return os;
            }


            Judge:: ~Judge() noexcept
            {

            }

            Judge:: Judge(const Laws &_laws) :
            laws(_laws),
            zero(),
            bpool(),
            blist(bpool),
            basis(bpool),
            house(laws.clan->size),
            xadd(),
            iadd(),
            Caux(laws.clan->size),
            lu(laws.rank),
            Prj(laws.clan->size,laws.clan->size),
            den(laws.clan->size),
            slist(),
            next(0),
            prev(0)
            {
            }

            static inline
            SignType CompareBroken(const Broken &lhs, const Broken &rhs) noexcept
            {
                return Sign::Of(lhs.xs,rhs.xs);
            }

            static inline bool isUnit(const Readable<apz> &v,
                                      const apz           &d,
                                      const size_t         j) noexcept
            {
                assert(j>0);
                assert(v.size()>=j);

                if(1!=d) return false;

                for(size_t i=v.size();i>j;--i) if(__Zero__ != v[i].s) return false;
                if(1!=v[j]) return false;
                for(size_t i=j-1;i>0;--i) if(__Zero__ != v[i].s) return false;

                return true;
            }

            void Judge:: abide(XMLog &xml, XWritable &Ctop)
            {
                Y_XML_Section(xml, "abide");
                blist.free();
                slist.free();

                //--------------------------------------------------------------
                //
                //
                // detect initial excess
                //
                //
                //--------------------------------------------------------------
                {
                    Y_XML_Section(xml, "initialExcess");
                    for(const Law *law=laws->head;law;law=law->next)
                    {
                        const xreal_t xs = law->excess(xadd,Ctop,TopLevel);
                        if(xs<=zero) continue;
                        const Broken b(*law,xs);
                        blist << b;

                    }

                    if(blist.size()<=0) {
                        Y_XMLog(xml, "[[ no excess detected ]]");
                        return;
                    }

                    blist.sort(CompareBroken);
                    for(const BNode *bn=blist->head;bn;bn=bn->next)
                    {
                        Y_XMLog(xml,"[*] " << **bn);
                    }
                }

                //--------------------------------------------------------------
                //
                //
                // extract the smallest excess base
                //
                //
                //--------------------------------------------------------------
                size_t iter=0;
            REDUCE:
                {
                    ++iter;
                    const size_t inxs = blist->size;
                    const size_t rank = laws.rank;
                    Y_XML_Section_Attr(xml, "extractBasis", Y_XML_Attr(inxs) << Y_XML_Attr(rank) << Y_XML_Attr(iter));

                    house.free();
                    basis.free();
                    for(size_t i=inxs;i>0;--i)
                    {
                        const Broken & broken = **blist->head;
                        if(Ortho::Vector *v = house.accepts(broken.law.alpha) )
                        {
                            house.progeny(v);
                            basis->pushTail( blist->popHead() );
                            if(house->size>=rank) break;
                        }
                        else
                        {
                            blist->moveHeadToTail();
                        }
                    }

                    Y_XMLog(xml, "basis:");
                    for(const BNode *bn=basis->head;bn;bn=bn->next)
                    {
                        const Broken &broken = **bn;
                        Y_XMLog(xml, "[+] " << broken);
                        for(const Actor *a=broken.law->head;a;a=a->next)
                        {
                            const Species &sp = a->sp;
                            if(!slist.found(sp)) slist << sp;
                        }
                    }

                    if(blist->size)
                    {
                        Y_XMLog(xml, "remaining");
                        for(const BNode *bn=blist->head;bn;bn=bn->next)
                        {
                            const Broken &broken = **bn;
                            Y_XMLog(xml, "[-] " << broken);
                        }
                    }
                }

                {
                    const size_t n = basis->size;
                    const size_t m = laws.clan->size;

                    //----------------------------------------------------------
                    //
                    // fill conservation topologies
                    //
                    //----------------------------------------------------------
                    Matrix<apz> Alpha(n,m);
                    Matrix<apz> AlphaT(m,n);
                    Matrix<apz> A3(n,m);
                    Matrix<apz> adj2(n,n);

                    {
                        size_t i = 1;
                        for(const BNode *bn=basis->head;bn;bn=bn->next,++i)
                        {
                            const Broken &broken = **bn;
                            Alpha[i].ld( broken.law.alpha );
                        }
                    }
                    AlphaT.assign(TransposeOf,Alpha);

                    //----------------------------------------------------------
                    //
                    // Compute Gram
                    //
                    //----------------------------------------------------------
                    Matrix<apz>          Alpha2(n,n);
                    MKL::Tao::Gram(iadd,Alpha2,Alpha);

                    //----------------------------------------------------------
                    //
                    // Compute determinant
                    //
                    //----------------------------------------------------------
                    const apz det2 = lu.determinant(Alpha2);
                    if(__Zero__==det2.s) throw Specific::Exception("Laws","corrupted coefficients");

                    //----------------------------------------------------------
                    //
                    // Compute adjoint
                    //
                    //----------------------------------------------------------
                    lu.adjoint(adj2,Alpha2);
                    MKL::Tao::MMul(iadd,A3,adj2,Alpha);
                    MKL::Tao::MMul(iadd,Prj,AlphaT,A3);

                    //----------------------------------------------------------
                    //
                    // Compute projection matrix
                    //
                    //----------------------------------------------------------
                    for(size_t i=m;i>0;--i)
                    {
                        for(size_t j=m;j>i;--j)   Sign::MakeOpposite( Coerce(Prj[i][j].s) );
                        for(size_t j=i-1;j>0;--j) Sign::MakeOpposite( Coerce(Prj[i][j].s) );
                        Prj[i][i] = det2 - Prj[i][i];
                    }
                    std::cerr << "P=" << Prj << "/" << det2 << std::endl;

                    //----------------------------------------------------------
                    //
                    // Compute simplification per row
                    //
                    //----------------------------------------------------------
                    for(size_t j=m;j>0;--j)
                    {
                        den[j] = det2;
                        Apex::Simplify::Array(Prj[j],den[j]);
                    }

                    //----------------------------------------------------------
                    //
                    // upgrade species
                    //
                    //----------------------------------------------------------
                    laws.dowload(Caux,Ctop);
                    for(const SNode *sn=laws.clan->head;sn;sn=sn->next)
                    {
                        const Species       & s = **sn;
                        const size_t          j = s.indx[AuxLevel];
                        const Readable<apz> & v = Prj[j];
                        const apz           & d = den[j];
                        if(isUnit(v,d,j)) {
                            continue;
                        }

                        xadd.ldz();
                        for(size_t i=m;i>0;--i)
                        {
                            const apz zcf = v[i]; if(__Zero__==zcf.s) continue;
                            const int icf = zcf.cast<int>("projection coefficient");
                            xadd.addProd(icf,Caux[i]);
                        }
                        const xreal_t D = d.cast<int>("projection denominator");
                        const xreal_t c = xadd.sum() / D;
                        std::cerr << "[" << s << "] =" << c.str() << std::endl;
                        s(Ctop,TopLevel) = c;
                    }

                    for(const BNode *bn=basis->head;bn;bn=bn->next)
                    {
                        const Law &   law = (**bn).law;
                        const xreal_t xs = law.excess(xadd,Ctop,TopLevel);
                        std::cerr << "basis: " << xs.str() << " @" << law << std::endl;
                    }

                    //----------------------------------------------------------
                    //
                    // keep only still broken laws
                    //
                    //----------------------------------------------------------
                    for(size_t i=blist->size;i>0;--i)
                    {
                        Broken &broken = **blist->head;
                        if(broken.still(xadd,Ctop))
                        {
                            blist->moveHeadToTail();
                        }
                        else
                        {
                            blist.popHead();
                        }
                    }

                    if(blist->size)
                    {
                        Y_XMLog(xml, "still broken:");
                        blist.sort(CompareBroken);
                        for(const BNode *bn=blist->head;bn;bn=bn->next)
                        {
                            const Broken &broken = **bn;
                            Y_XMLog(xml, "[-] " << broken);
                        }
                        goto REDUCE;
                    }

                }


            }

        }

    }

}
