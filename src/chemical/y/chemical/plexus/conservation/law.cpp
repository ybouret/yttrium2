

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/stream/output.hpp"
#include "y/apex/simplify.hpp"
#include "y/mkl/tao/3.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Remedy:: ~Remedy() noexcept
            {
            }

            Remedy:: Remedy(const size_t n, const size_t m) :
            Object(),
            numer(n,m),
            denom(n)
            {
            }
            
        }

    }

}

#include "y/chemical/type/list-ops.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Law:: Projection:: ~Projection() noexcept {}

            Law:: Projection:: Projection(const size_t n) : Remedy(n,n) { }


            void  Law:: Projection:: compute(const Actors & law,
                                             XAdd         & xadd,
                                             XWritable    & Ctop,
                                             XWritable    & Ctmp) const
            {
                const size_t n = numer.rows;
                for(size_t i=n;i>0;--i)
                {

                    xadd.ldz();
                    {
                        const XReadable &p = numer[i];
                        size_t j=1;
                        for(const Actor *a=law->head;a;a=a->next,++j)
                        {
                            xadd << p[j] * a->sp(Ctop,TopLevel);
                        }
                    }
                    Ctmp[i] = xadd.sum() / denom[i];
                }

                {
                    size_t i=1;
                    for(const Actor *a=law->head;a;a=a->next,++i)
                    {
                        a->sp(Ctop,TopLevel) = Ctmp[i];
                    }
                }
            }
        }

    }
}


#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Law:: Correction:: ~Correction() noexcept {}

            Law:: Correction:: Correction(const size_t n, const size_t m) :
            Remedy(n,m)
            {
            }

            void  Law:: Correction:: compute(const Law    & law,
                                             XAdd         & xadd,
                                             XWritable    & Ctop,
                                             XWritable    & xi,
                                             XWritable    & Ctmp,
                                             Accumulator  & Cnew) const
            {
                //--------------------------------------------------------------
                // initialize Cnew
                //--------------------------------------------------------------
                Algo::ForEach(Cnew,&XAdd::ldz);

                //--------------------------------------------------------------
                // gather concentrations in Ctmp and initialize Cnew
                //--------------------------------------------------------------
                {
                    size_t j=0;
                    for(const Actor *a=law->head;a;a=a->next)
                    {
                        const Species &sp = a->sp;
                        sp(Cnew,SubLevel) << (Ctmp[++j] = sp(Ctop,TopLevel));
                        law.display(std::cerr << "[",a->sp.name,Justify::Center) << "] = " << Ctmp[j].str() << std::endl;
                    }
                    assert(numer.cols==j);
                }

                //--------------------------------------------------------------
                // computing xi and dispatch deltaC
                //--------------------------------------------------------------
                const size_t m = numer.cols;
                {
                    size_t i=0;
                    for(const ENode *en=law.lead->head;en;en=en->next)
                    {
                        const Equilibrium & eq = **en;
                        const XReadable   & cf = numer[++i];
                        xadd.ldz(); for(size_t j=m;j>0;--j) xadd += Ctmp[j] * cf[j];
                        const xreal_t x = (xi[i] = xadd.sum() / denom[i]);
                        eq.displayCompact(eq.print(std::cerr << "xi_" << eq.name << " = " << xi[i].str() << " @") << " ",
                                          Ctop,TopLevel) << std::endl;

                        for(const Actor *a=eq.prod->head;a;a=a->next)
                        {
                            a->sp(Cnew,SubLevel) += (x*a->xn);
                        }

                        for(const Actor *a=eq.reac->head;a;a=a->next)
                        {
                            a->sp(Cnew,SubLevel) -= (x*a->xn);
                        }
                    }
                }

                for(const SNode *sn=law.clan->head;sn;sn=sn->next)
                {
                    const Species &sp = **sn;
                    const xreal_t  cc = sp(Ctop,TopLevel) = sp(Cnew,SubLevel).sum();
                    std::cerr << "\t[" << sp << "]=" << cc.str() << std::endl;
                }

                
            }

        }
    }

}


#include "y/mkl/algebra/lu.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Law:: ~Law() noexcept
            {
            }

            Law:: Law() :
            Actors(Actor::InConservation),
            prj(0),
            cor(0),
            ua2(0),
            xa2(0),
            norm(0),
            lead(),
            zero(0),
            next(0),
            prev(0)
            {

            }

            std::ostream & operator<<(std::ostream &os, const Law &law)
            {
                os << "d_(" << law.name << ")";
                return os;
            }


            xreal_t Law:: excess(XAdd &xadd, const XReadable &C, const Level L) const
            {
                xadd.ldz();
                for(const Actor *a = list.head; a; a=a->next)
                {
                    const xreal_t c = a->sp(C,L);
                    for(unsigned n=a->nu;n>0;--n) xadd << c;
                }
                const xreal_t xs = xadd.sum();
                if(xs<zero) return -xs;
                return zero;
            }

            OutputStream & Law:: viz(OutputStream &fp, const String &color) const
            {
                nodeName(fp) << "[";
                fp << "label= < " << html() << " >,color=" << color << ", fontcolor=" << color;
                fp << ",shape=box,style=diagonals";
                Endl(fp<<"]");
                for(const Actor *a=list.head;a;a=a->next)
                {
                    Endl(to( &(a->sp),fp) << "[color=" << color << ",arrowhead=odot]");
                }
                return fp;
            }

           
            static inline
            size_t CommonSpecies(const Law &law, const Readable<int> &nu) noexcept
            {
                size_t res = 0;
                for(const Actor *a=law->head;a;a=a->next)
                {
                    if( a->sp(nu,SubLevel) ) ++res;
                }
                return res;
            }


            using namespace MKL;

            void Law:: finalize(XMLog &         xml,
                                const EList &   primary,
                                const iMatrix & topology)
            {
                //--------------------------------------------------------------
                //
                // precompute
                //
                //--------------------------------------------------------------
                {
                    apn sum = 0;
                    for(const Actor *a = list.head;a;a=a->next)
                    {
                        sum += apn(a->nu).sqr();
                    }
                    Coerce(ua2)  = sum.cast<unsigned>("|Law|^2");
                    Coerce(xa2)  = ua2;
                    Coerce(norm) = xa2.sqrt();
                }

                //--------------------------------------------------------------
                //
                // compute projections
                //
                //--------------------------------------------------------------
                computeProjection();

                //--------------------------------------------------------------
                //
                // compute lead
                //
                //--------------------------------------------------------------
                for(const ENode *en = primary->head;en;en=en->next)
                {
                    const Equilibrium   & eq = **en;
                    const Readable<int> & nu = topology[ eq.indx[SubLevel] ];
                    if( CommonSpecies(*this,nu) >= 2) Coerce(lead) << eq;
                }

                //--------------------------------------------------------------
                //
                // compute clan
                //
                //--------------------------------------------------------------
                for(const ENode *en = primary->head;en;en=en->next)
                {
                    const Equilibrium & eq = **en;
                    eq.mergeSpeciesInto( Coerce(clan) );
                }
                ListOps::Sort( Coerce(clan) );

                //--------------------------------------------------------------
                //
                // compute correction matrix
                //
                //--------------------------------------------------------------
                computeCorrection();
            }


            void Law:: project(XAdd        & xadd,
                               XWritable   & Ctop,
                               XWritable   & Ctmp) const
            {
                prj->compute(*this,xadd,Ctop,Ctmp);
            }


            void Law:: nullify(XAdd        & xadd,
                               XWritable   & Ctop,
                               XWritable   & Xi,
                               XWritable   & Ctmp,
                               Accumulator & Cnew) const
            {
                cor->compute(*this,xadd,Ctop,Xi,Ctmp,Cnew);
            }

            void Law:: computeProjection()
            {
                const size_t  n = list.size;
                CxxArray<apz> alpha(n);
                {
                    size_t i=1;
                    for(const Actor *a = list.head;a;a=a->next,++i)
                        alpha[i] = a->nu;
                }
                Matrix<apz>   mproj(n,n);
                {
                    const apz     a2 = ua2;
                    for(size_t i=n;i>0;--i)
                    {
                        const apz alpha_i = alpha[i];
                        for(size_t j=n;j>i;--j)   mproj[i][j] = - alpha_i * alpha[j];
                        mproj[i][i] = a2 - alpha_i.sqr();
                        for(size_t j=i-1;j>0;--j) mproj[i][j] = - alpha_i * alpha[j];
                    }
                    for(size_t i=1;i<=n;++i)
                    {
                        alpha[i] = a2;
                        Apex::Simplify::Array(mproj[i],alpha[i]);
                    }
                }

                Coerce(prj) = new Projection(n);
                for(size_t i=1;i<=n;++i)
                {
                    for(size_t j=1;j<=n;++j)
                        Coerce(prj->numer[i][j]) = mproj[i][j].cast<int>("projection numerator");
                    Coerce(prj->denom[i]) = alpha[i].cast<unsigned>("projection denominator");
                }
            }


            void Law:: computeCorrection()
            {
                const size_t n = lead->size;
                const size_t m = list.size;


                Coerce(cor) = new Correction(n,m);
                Matrix<apz>  Nil(n,m);
                Matrix<apz>  Nu(n,m);
                {
                    size_t i=1;
                    for(const ENode *en = lead->head;en;en=en->next,++i)
                    {
                        const Equilibrium &eq = **en;
                        size_t             j  = 1;
                        for(const Actor *a=list.head;a;a=a->next,++j)
                        {
                            Nu[i][j] = eq.stoichiometry(a->sp);
                        }
                    }
                }
                Matrix<apz>          G(n,n);
                Cameo::Addition<apz> iadd;
                Tao::Gram(iadd,G,Nu);
                LU<apq>              lu(n);
                const apz            dG = lu.determinant(G);
                if( __Zero__ == dG.s) throw Specific::Exception(CallSign,"unexpected singular correction");
                Matrix<apz>          aG(n,n);
                lu.adjoint(aG,G);
                Tao::MMul(iadd,Nil,aG,Nu);
                CxxArray<apz>        Den(n,dG);
                for(size_t i=1;i<=n;++i)
                {
                    Apex::Simplify::Array(Nil[i], Den[i]);
                    Coerce(cor->denom[i]) = (real_t) Den[i].cast<int>("correction denominator");
                    for(size_t j=1;j<=m;++j)
                        Coerce(cor->numer[i][j]) = - (real_t) Nil[i][j].cast<int>("correction numerator");
                }



            }
        }

    }

}
