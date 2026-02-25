

//! \file

#ifndef Y_Calculus_Prime_Prev_Included
#define Y_Calculus_Prime_Prev_Included 1

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
         \return p<=n
         */
        template <typename T, typename TEST> inline
        T FindPrev(T n, TEST &isPrime) noexcept
        {
            assert(n>0);
            static const T zero  = 0;
            static const T one   = 1;
            static const T two   = 2;
            static const T three = 3;
            if(n<=three) return n;
            assert(n>=4);
            if(zero==(n&one)) --n;
            assert(one==(n&one));
            while( !isPrime(n) ) n -= two;
            return n;
        }

        //! \param n starting positive value \return prev prime with basic test
        template <typename T> inline
        T Prev(const T n) noexcept
        {
            assert(n>0);
            return FindPrev(n,Prime::Test<T>);
        }


    }
}

#endif // !Y_Calculus_Prime_Prev_Included
