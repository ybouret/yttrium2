
//! \file


#ifndef Y_MKL_AlmostEqual_Included
#define Y_MKL_AlmostEqual_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/mkl/numeric.hpp"
#include "y/core/utils.hpp"
#include "y/memory/stealth.hpp"
#include "y/mkl/api/scalar.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {

            template <typename T>
            inline bool  ScalAreAlmostEqual(const T &x,
                                            const T &y)
            {
                const T ax  = MKL::Fabs<T>::Of(x);
                const T ay  = MKL::Fabs<T>::Of(y);
                const T del = x-y;
                const T lhs = MKL::Fabs<T>::Of(del);
                const T ma  = Min(ax,ay);
                const T rhs = Max(ma,Numeric<T>::THETA);
                return lhs <= Numeric<T>::EPSILON * rhs;
            }


            template <typename T>
            inline bool VectAreAlmostEqual(const T &lhs, const T &rhs)
            {
                for(size_t i=T::DIMENSIONS;i>0;--i)
                {
                    if(!ScalAreAlmostEqual(lhs[i],rhs[i]))
                        return false;
                }
                return true;
            }



        }

        template <typename T>
        struct AlmostEqual
        {
            Y_Args_Declare(T,Type);

            static inline bool Are(ParamType lhs, ParamType rhs)
            {
                static const IntToType< IsScalar<MutableType>::Value > selected  = {};
                return Are(lhs,rhs,selected);
            }

            static inline bool Are(ConstType &lhs, ConstType &rhs, const IntToType<true> &)
            {
                return Kernel::ScalAreAlmostEqual(lhs,rhs);
            }

            static inline bool Are(ConstType &lhs, ConstType &rhs, const IntToType<false> &)
            {
                return Kernel::VectAreAlmostEqual(lhs,rhs);
            }
        };




    }
}

#endif

