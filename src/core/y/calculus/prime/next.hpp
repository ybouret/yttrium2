
//! \file

#ifndef Y_Calculus_Prime_Next_Included
#define Y_Calculus_Prime_Next_Included 1

#include "y/calculus/prime/test.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Prime
    {
        //! find next prime with given test
        /**
         \param n sarting value
         \param isPrime test procedure
         \return p>=n
         */
        template <typename T, typename TEST> inline
        T FindNext(T n, TEST &isPrime) noexcept
        {
            static const T one = 1;
            static const T two = 2;
            static const T three = 3;
            if(n<=one)   return one;
            if(n<=three) return n;
            assert(n>=4);
            n |= one;
            while(! isPrime(n) ) n += two;
            return n;
        }

        //! \param n starting value \return next prime with basic test
        template <typename T> inline
        T Next(const T n) noexcept
        {
            return FindNext(n,Prime::Test<T>);
        }
    }
}

#endif // !Y_Calculus_Prime_Next_Included
