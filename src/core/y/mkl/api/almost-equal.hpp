
//! \file


#ifndef Y_MKL_AlmostEqual_Included
#define Y_MKL_AlmostEqual_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/mkl/numeric.hpp"
#include "y/core/utils.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            template <typename T> inline
            bool  AreAlmostEqual(const T &x,
                                      const T &y) noexcept
            {
                static const T & ftol  = Numeric<T>::EPSILON;
                static const T & ztol  = Numeric<T>::MIN;
                const T          vmin  = Min(MKL::Fabs<T>::Of(x),MKL::Fabs<T>::Of(y));
                const T          delta = x-y;

                if(vmin<=0.0) {
                    return MKL::Fabs<T>::Of(delta)<=ztol;
                }

                return (MKL::Fabs<T>::Of((delta)/Max(ztol,vmin)))<=ftol;
            }
        }

        template <typename> struct AlmostEqual;

        template <typename T, template <typename> class VECT>
        struct  AlmostEqual< VECT<T> >
        {
            Y_Args_Expose(T,Type);
            typedef VECT<T> VTX;

            static inline bool Are(const VTX &lhs, const VTX &rhs)
            {
                ConstType *l = Memory::Stealth::Cast<Type>( &lhs );
                ConstType *r = Memory::Stealth::Cast<Type>( &rhs );
                for(size_t i=VTX::DIMENSIONS;i>0;--i)
                {
                    if(!Kernel::AreAlmostEqual(*(l++),*(r++)))
                    {
                        return false;
                    }
                }
                return true;
            }
        };

        template <typename T>
        struct  AlmostEqual
        {
            Y_Args_Declare(T,Type);
            static inline bool Are(ParamType lhs, ParamType rhs)
            {
                return Kernel::AreAlmostEqual(lhs,rhs);
            }
        };



    }
}

#endif

