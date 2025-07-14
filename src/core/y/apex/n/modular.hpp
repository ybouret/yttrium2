

//! \file

#ifndef Y_Apex_Modular_Included
#define Y_Apex_Modular_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Modular Arithmetic
        //
        //
        //______________________________________________________________________
        struct Modular
        {
            //! Modular Exponentiation
            /**
             \param b value
             \param e exponent
             \param n modulus
             \return b^e[n]
             */
            static Natural Exp(const Natural &b,
                               const Natural &e,
                               const Natural &n);

            //! Modular Inverse
            /**
             \param a value
             \param n modulus
             \return a^(-1)[n]
             */
            static Natural Inv(const Natural &a,
                               const Natural &n);
        };

    }
}

#endif

