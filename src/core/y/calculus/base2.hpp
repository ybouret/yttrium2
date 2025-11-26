
//! \file

#ifndef Y_Calculus_Base2_Included
#define Y_Calculus_Base2_Included 1

#include "y/type/ints.hpp"
#include <cassert>

namespace Yttrium
{

    //! Test is x is a power of two
    /** \param x integral type \return true if x==2^n */
    template <typename T>
    inline bool IsPowerOfTwo(const T x) noexcept
    {
        static const T _1 = 1;
        return x && (!(x & (x -_1) ));
    }

    //! Metrics for Base2 operations
    template <typename T>
    struct Base2
    {
        typedef T             Type;                                          //!< alias
        static const Type     One        = Type(1);                          //!< alias
        static const unsigned Size       = sizeof(Type);                     //!< in bytes
        static const unsigned Bits       = Size << 3;                        //!< bit count
        static const bool     SignedType = IsSigned<T>::Value;               //!< alias
        static const unsigned MaxShift   = SignedType ? (Bits-2) : (Bits-1); //!< max shift
        static const Type     MaxBytes   = One << MaxShift;                  //!< max value
    };



    //! Find next power of two
    /**
     \param x <= Base2<T>::MaxValue
     \return n=2^p>=x
     */
    template <typename T>
    inline T NextPowerOfTwo(const T x) noexcept
    {
        assert( x <= Base2<T>::MaxBytes );
        T n = Base2<T>::One;
        while(n<x) n <<= 0x1;
        return n;
    }

    //! Find next power of two and log2
    /**
     \param x <= Base2<T>::MaxValue
     \param p computed in loop
     \return n=2^p>=x
     */
    template <typename T>
    inline T NextPowerOfTwo(const T x, unsigned &p) noexcept
    {
        assert( x <= Base2<T>::MaxBytes );
        T n = Base2<T>::One;
        p   = 0;
        while(n<x)
        {
            n <<= 0x1;
            ++p;
        }
        assert( Base2<T>::One << p == n);
        return n;
    }

    //! compute log2 of an exact power of two
    /**
     \param powerOfTwo = 2^p
     \return p
     */
    template <typename T> inline
    unsigned ExactLog2(const T powerOfTwo) noexcept
    {
        assert(IsPowerOfTwo(powerOfTwo));
        unsigned shift = 0;
        T        value = 1;
        while(value!=powerOfTwo)
        {
            value <<= 1;
            ++shift;
        }
        return shift;
    }

    //! compute log2 of an next power of two
    /**
     \param x <= 2^p
     \return p
     */
    template <typename T> inline
    unsigned CeilLog2(const T x) noexcept
    {
        assert( x <= Base2<T>::MaxBytes );
        T        n = Base2<T>::One;
        unsigned p = 0;
        while(n<x)
        {
            n <<= 0x1;
            ++p;
        }
        assert( Base2<T>::One << p == n);
        return p;
    }

    //! Find previous power of two
    /**
     \param x positive value
     \return 2^n <= x
     */
    template <typename T>
    inline T PrevPowerOfTwo(const T x) noexcept
    {
        assert(x>0);
        T n = Base2<T>::MaxBytes;
        while(n>x) n >>= 1;
        return n;
    }




}

#endif
