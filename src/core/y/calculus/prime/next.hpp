
//! \file

#ifndef Y_Calculus_Prime_Next_Included
#define Y_Calculus_Prime_Next_Included 1

#include "y/calculus/prime/test.hpp"

namespace Yttrium
{
    namespace Prime
    {
        template <typename T, typename TEST> inline
        T FindNext(T n, TEST &isPrime) noexcept
        {
            while(! isPrime(n) ) n += 2;
            return n;
        }

        template <typename T> inline
        T Next(T n) noexcept
        {
            return FindNext(n,Prime::Test<T>);
        }
    }
}

#endif // !Y_Calculus_Prime_Next_Included
