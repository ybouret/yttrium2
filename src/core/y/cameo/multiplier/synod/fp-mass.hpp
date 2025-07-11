
//! \file

#ifndef Y_Cameo_Multipler_FP_Mass_Included
#define Y_Cameo_Multipler_FP_Mass_Included 1

#include "y/type/args.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/complex.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        namespace Synod
        {
            
            template <typename T>
            struct FPointMass;

            template <typename T>
            struct FPointMass
            {
                static int Get(const T &x) noexcept {
                    int mass = 0;
                    (void) std::frexp(x,&mass);
                    return mass;
                }
            };

            template <typename T>
            struct FPointMass< XReal<T> >
            {
                static int Get(const XReal<T> &x) noexcept { return x.exponent; }
            };

            template <typename T>
            struct FPointMass< Complex<T> >
            {
                static int Get(const Complex<T> &x) noexcept
                {
                    const T _ = x.abs();
                    return FPointMass<T>::Get(_);
                }
            };


            template <typename T>
            struct FPointMass< Complex< XReal<T> > >
            {
                static int Get(const Complex< XReal<T> > &x) noexcept
                {
                    const XReal<T> _ = x.abs();
                    return _.exponent;
                }
            };
        }

        template <typename T> inline
        int GetFPointMass(const T &x) noexcept
        {
            return Synod::FPointMass<T>::Get(x);
        }
    }

}

#endif

