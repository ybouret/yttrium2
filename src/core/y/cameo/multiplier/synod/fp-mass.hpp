
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
            struct FPointMass; //!< generic mass computation

            //! default for floating point
            template <typename T>
            struct FPointMass
            {
                //! \param x floating point \return exponent
                static int Get(const T &x) noexcept {
                    int mass = 0;
                    (void) std::frexp(x,&mass);
                    return mass;
                }
            };

            //! for XReal
            template <typename T>
            struct FPointMass< XReal<T> >
            {
                //! \param x floating point \return exponent
                static int Get(const XReal<T> &x) noexcept { return x.exponent; }
            };

            //! for floating point complex
            template <typename T>
            struct FPointMass< Complex<T> >
            {
                //! \param x floating point \return exponent of |x|
                static int Get(const Complex<T> &x) noexcept
                {
                    const T _ = x.abs();
                    return FPointMass<T>::Get(_);
                }
            };

            //! for XReal complex
            template <typename T>
            struct FPointMass< Complex< XReal<T> > >
            {
                //! \param x floating point \return exponent
                static int Get(const Complex< XReal<T> > &x) noexcept
                {
                    const XReal<T> _ = x.abs();
                    return _.exponent;
                }
            };
        }

        //! \param x any floating point \return exponent as mass
        template <typename T> inline
        int GetFPointMass(const T &x) noexcept
        {
            return Synod::FPointMass<T>::Get(x);
        }
    }

}

#endif

