
//! \file

#ifndef Y_MKL_Statistics_Descriptive_Included
#define Y_MKL_Statistics_Descriptive_Included 1

#include "y/cameo/addition.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/static/moniker.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/sqrt.hpp"


namespace Yttrium
{
    namespace MKL
    {

        namespace Statistics
        {

            template <typename T>
            class Descriptive
            {
            public:
                typedef typename FCPU<T>::Type fcpu_t;
                Y_Args_Declare(T,Type);

                inline explicit Descriptive() : xadd(), zero() {}
                inline virtual ~Descriptive() noexcept {}


                template <typename ITER> inline
                T average(ITER it, size_t n)
                {
                    if(n<=0) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0) xadd << *(it++);
                    return xadd.sum()/denom;
                }

                template <typename SEQ> inline
                T average(const SEQ &seq) { return average(seq.begin(),seq.size()); }

                template <typename ITER> inline
                T variance(ITER it, size_t n, ParamType ave)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)(n-1);
                    xadd.ldz();
                    while(n-- > 0) {
                        ConstType delta = *(it++)-ave;
                        ConstType delsq = delta*delta;
                        xadd << delsq;
                    }
                    return xadd.sum()/denom;
                }

                template <typename SEQ> inline
                T variance(const SEQ &seq, ParamType ave)
                {
                    return variance(seq.begin(),seq.size(),ave);
                }

                template <typename ITER> inline
                T stddev(ITER it, size_t n, ParamType ave)
                {
                    const T var = variance(it,n,ave);
                    return Sqrt<T>::Of(var);
                }

                template <typename SEQ> inline
                T stddev(const SEQ &seq, ParamType ave)
                {
                    const T var = variance(seq,ave);
                    return Sqrt<T>::Of(var);
                }

                template <typename ITER> inline
                T absdev(ITER it, size_t n, ParamType ave)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0) {
                        ConstType delta = *(it++)-ave;
                        ConstType del_a = Fabs<T>::Of(delta);
                        xadd << del_a;
                    }
                    return xadd.sum()/denom;
                }

                template <typename SEQ> inline
                T absdev(const SEQ &seq, ParamType ave)
                {
                    return absdev(seq.begin(),seq.size(),ave);
                }

                Cameo::Addition<T>               xadd;
                const Static::Moniker<ConstType> zero;

            private:
                Y_Disable_Copy_And_Assign(Descriptive);
            };
        }

    }

}

#endif // !Y_MKL_Statistics_Descriptive_Included
