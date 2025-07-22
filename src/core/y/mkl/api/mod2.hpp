//! \file

#ifndef Y_MKL_Mod2_Included
#define Y_MKL_Mod2_Included 1

#include "y/mkl/api/scalar.hpp"
#include "y/container/ordered/static-priority-queue.hpp"
#include "y/check/static.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {

            template <typename T,bool SCALAR> struct Mod2;

            template <typename T>
            struct Mod2<T,true>
            {
                Y_Args_Expose(T,Type);
                typedef ConstType ReturnType;

                static inline ReturnType Compute(ConstType &scal)
                {
                    return scal*scal;
                }
            };

            template <typename T, const size_t N>
            struct VMod2;

            template <typename T>
            struct VMod2<T,1>
            {
                static typename T::Type Compute(const T &vect)
                {
                    return Squared(vect[1]);
                }
            };

            template <typename T>
            struct VMod2<T,2>
            {
                static typename T::Type Compute(const T &vect)
                {
                    return Squared(vect[1]) + Squared(vect[2]);
                }
            };

            template <typename T,size_t N>
            struct VMod2
            {
                static typename T::Type Compute(const T &vect)
                {
                    Y_STATIC_CHECK(N>=3,BadDims);
                    typedef typename T::Type scalar_t;
                    StaticPriorityQueue<scalar_t,N> Q;
                    for(size_t i=1;i<=N;++i) Q << Squared(vect[i]);
                    while(Q->size>1)
                    {
                        const scalar_t lhs = Q.pop();
                        const scalar_t rhs = Q.pop();
                        Q << (lhs+rhs);
                    }
                    return Q.pop();
                }
            };

            //! vectorial
            template <typename T>
            struct Mod2<T,false>
            {
                Y_Args_Expose(T,Type);
                typedef typename T::Type ReturnType;

                static inline ReturnType Compute(ConstType &vect)
                {
                    return VMod2<T,T::DIMENSIONS>::Compute(vect);
                }
            };



        }

        template <typename T>
        struct Mod2
        {
            Y_Args_Declare(T,Type);
            typedef Kernel::Mod2<MutableType,IsScalar<MutableType>::Value> API;

            static inline
            typename API::ReturnType Of(ParamType lhs)
            {
                return API::Compute(lhs);
            }
        };

    }

}

#endif

