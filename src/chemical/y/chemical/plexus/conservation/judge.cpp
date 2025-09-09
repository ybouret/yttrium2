
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
            xadd()
            {
            }

            static inline
            SignType CompareBroken(const Broken &lhs, const Broken &rhs) noexcept
            {
                return Sign::Of(lhs.xs,rhs.xs);
            }

            void Judge:: abide(XMLog &xml, XWritable &Ctop)
            {
                Y_XML_Section(xml, "abide");
                blist.free();

                {
                    Y_XML_Section(xml, "excess");
                    for(const Law *law=laws->head;law;law=law->next)
                    {
                        const xreal_t xs = law->excess(xadd,Ctop,TopLevel);
                        if(xs<=zero) continue;
                        const Broken b(*law,xs);
                        blist << b;

                    }

                    if(blist.size()<=0)
                    {
                        Y_XMLog(xml, "[[ no excess ]]");
                        return;
                    }
                    blist.sort(CompareBroken);
                    for(const BNode *bn=blist->head;bn;bn=bn->next)
                    {
                        Y_XMLog(xml,"[#] " << **bn);
                    }
                }

                {
                    const size_t excessive = blist->size;
                    Y_XML_Section_Attr(xml, "extractBasis", Y_XML_Attr(excessive) );
                    const size_t nmax = laws.rank;
                    house.free();
                    basis.free();
                    for(size_t i=excessive;i>0;--i)
                    {
                        const Broken & broken = **blist->head;
                        if(Ortho::Vector *v = house.accepts(broken.law.alpha) )
                        {
                            house.progeny(v);
                            basis->pushTail( blist->popHead() );
                            if(house->size>=nmax) break;
                        }
                        else
                        {
                            blist->pushTail(blist->popHead());
                        }
                    }

                    Y_XMLog(xml, "basis:");
                    for(const BNode *bn=basis->head;bn;bn=bn->next)
                    {
                        const Broken &broken = **bn;
                        Y_XMLog(xml, "[+] " << broken);
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

                    Matrix<apz> Alpha(n,m);
                    Matrix<apz> AlphaT(m,n);
                    size_t i = 1;
                    for(const BNode *bn=basis->head;bn;bn=bn->next,++i)
                    {
                        const Broken &broken = **bn;
                        Alpha[i].ld( broken.law.alpha );
                    }
                    AlphaT.assign(TransposeOf,Alpha);
                    std::cerr << "Alpha=" << Alpha << std::endl;

                    Matrix<apz>          Alpha2(n,n);
                    Cameo::Addition<apz> iadd;
                    MKL::Tao::Gram(iadd,Alpha2,Alpha);
                    std::cerr << "Alpha2=" << Alpha2 << std::endl;
                    MKL::LU<apq> lu(n);
                    apz det2 = lu.determinant(Alpha2);
                    std::cerr << "det2=" << det2 << std::endl;
                    if(__Zero__==det2.s) throw Specific::Exception("Laws","corrupted coefficients");
                    Matrix<apz> adj2(n,n);
                    lu.adjoint(adj2,Alpha2);
                    std::cerr << "adj2=" << adj2 << std::endl;
                    Matrix<apz> A3(n,m);
                    MKL::Tao::MMul(iadd,A3,adj2,Alpha);
                    Matrix<apz> P(m,m);
                    MKL::Tao::MMul(iadd,P,AlphaT,A3);
                    std::cerr << "A4=" << P << std::endl;
                    for(size_t i=m;i>0;--i)
                    {
                        for(size_t j=m;j>i;--j)   Sign::MakeOpposite( Coerce(P[i][j].s) );
                        for(size_t j=i-1;j>0;--j) Sign::MakeOpposite( Coerce(P[i][j].s) );
                        P[i][i] = det2 - P[i][i];
                    }
                    std::cerr << "P=" << P << "/" << det2 << std::endl;
                    Apex::Simplify::Apply(P,det2);
                    std::cerr << "P=" << P << "/" << det2 << std::endl;

                }


            }

        }

    }

}
