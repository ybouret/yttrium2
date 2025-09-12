

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/stream/output.hpp"
#include "y/apex/simplify.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Law:: Projection:: ~Projection() noexcept {}

            Law:: Projection:: Projection(const size_t n) :
            numer(n,n),
            denom(n)
            {
            }


            void  Law:: Projection:: compute(const Law   & law,
                                             XAdd        & xadd,
                                             XWritable   & Ctop,
                                             XWritable   & Ctmp) const
            {
                const size_t n = numer.rows;
                for(size_t i=n;i>0;--i)
                {

                    xadd.ldz();
                    {
                        size_t j=1;
                        for(const Actor *a=law->head;a;a=a->next,++j)
                        {
                            
                        }
                    }

                    Ctmp[i] = xadd.sum() / denom[i];
                }
            }
        }

    }
}


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
            ua2(0),
            xa2(0),
            norm(0),
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

            void Law:: finalize()
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
                    std::cerr << "numer=" << prj->numer << std::endl;
                    std::cerr << "denom=" << prj->denom << std::endl;

                }

            }

        }
    }

}
