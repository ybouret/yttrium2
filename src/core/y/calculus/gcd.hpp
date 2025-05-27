
//! \file
#ifndef Y_Calculus_GCD_Included
#define Y_Calculus_GCD_Included 1

#include "y/system/compiler.hpp"
#include <cassert>
namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! GCD(a>0,b>0)
        /**
         \param a positive value
         \param b positive value
         \return Euclid's algorithm for gcd
         */
        //______________________________________________________________________
        template <typename T> inline
        T GreatestCommonDivisor(T a, T b) noexcept
        {
            assert(a>0);
            assert(b>0);
            if(a<b)
            {
                const T t = a;
                a = b;
                b = t;
            }
            assert(a>=b);
            while(b>0)
            {
                const T r = T(a%b);
                a = b;
                b = r;
            }

            return a;
        }
    }

    //__________________________________________________________________________
    //
    //
    //! GCD of integral types
    /**
     \param a any value
     \param b any value
     \return gcd of a,b
     */
    //__________________________________________________________________________
    template <typename T> inline
    T GreatestCommonDivisor(const T a, const T b) noexcept
    {
        if(a<=0)
        {
            if(b<=0)
            {
                return 1;
            }
            else
            {
                return b;
            }
        }
        else
        {
            assert(a>0);
            if(b<=0)
            {
                return a;
            }
            else
            {
                assert(b>0);
                return Core::GreatestCommonDivisor(a,b);
            }
        }
    }

    //! simplification of  (a,b) by their gcd
    /**
     \param a any value
     \param b any value
     */
    template <typename T> inline
    void SimplifyByGCD(T &a, T &b) noexcept
    {
        static const T _1(1);
        const T g = GreatestCommonDivisor(a,b);
        if(g>_1) { a/=g; b/=g; }
    }

}

#endif
