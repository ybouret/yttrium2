//! \file

#ifndef Y_Calculus_Prime_Test_Included
#define Y_Calculus_Prime_Test_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Prime
    {
        //! basic testing
        /**
         \param n unsigned value
         \return true if n is prime
         */
        template <typename T> inline
        bool Test(const T n) noexcept
        {
            if(n<=1) return false;
            if(n<=3) return true;
            if( 0 == (n%2) || 0 == (n%3) ) return false;
            T i = 5;
            while(i*i <= n) {
                if ( ( 0 == (n%i) ) ||  ( 0 == (n%(i+2) )  ) )
                    return false;
                i += 6;
            }
            return true;
        }
    }
}

#endif // !Y_Calculus_Prime_Test_Included
