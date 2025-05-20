
//! \file

#ifndef Y_Type_Ints_Included
#define Y_Type_Ints_Included 1

#include "y/system/types.hpp"
#include "y/type/list.hpp"
#include "y/type/pick.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    template <typename T> struct UnsignedInt;

    template <>
    struct UnsignedInt<uint8_t>
    {
        typedef uint8_t   Type;
        static const Type Minimum = 0x00;
        static const Type Maximum = 0xff;
    };

    template <>
    struct UnsignedInt<uint16_t>
    {
        typedef uint16_t  Type;
        static const Type Minimum = 0x0000;
        static const Type Maximum = 0xffff;
    };


    template <>
    struct UnsignedInt<uint32_t>
    {
        typedef uint32_t  Type;
        static const Type Minimum = 0x00000000;
        static const Type Maximum = 0xffffffff;
    };


    template <>
    struct UnsignedInt<uint64_t>
    {
        typedef uint64_t  Type;
        static const Type Minimum = 0x0000000000000000ULL;
        static const Type Maximum = 0xffffffffffffffffULL;
    };

    typedef TL4(UnsignedInt<uint8_t>,
                UnsignedInt<uint16_t>,
                UnsignedInt<uint32_t>,
                UnsignedInt<uint64_t>) UnsignedInts;

    template <typename T>
    struct UnsignedIntFor
    {
        enum { Index  = IntegerLog2For<T>::Value };
        typedef typename TL::TypeAt<UnsignedInts,Index>::Result Result;
    };



    template <typename T> struct SignedInt;

    template <>
    struct SignedInt<int8_t>
    {
        typedef int8_t    Type;
        static const Type Minimum = -128;
        static const Type Maximum =  127;
    };

    template <>
    struct SignedInt<int16_t>
    {
        typedef int16_t   Type;
        static const Type Minimum = -32768;
        static const Type Maximum =  32767;
    };


    template <>
    struct SignedInt<int32_t>
    {
        typedef int32_t   Type;
        static const Type Minimum = -2147483648;
        static const Type Maximum =  2147483647;
    };

    template <>
    struct SignedInt<int64_t>
    {
        typedef int64_t    Type;
        static const Type  Minimum = -9223372036854775807LL-1LL;
        static const Type  Maximum =  9223372036854775807LL;
    };


    typedef TL4(SignedInt<int8_t>,
                SignedInt<int16_t>,
                SignedInt<int32_t>,
                SignedInt<int64_t>) SignedInts;

    template <typename T>
    struct SignedIntFor
    {
        enum { Index  = IntegerLog2For<T>::Value };
        typedef typename TL::TypeAt<SignedInts,Index>::Result Result;
    };


    template <typename T> struct IsSigned
    {
        static const T n = T(-1);
        static const T p = T(1);
        static const bool Value = (n<p);
    };

    template <typename T>
    struct IntegerFor
    {
        typedef typename UnsignedIntFor<T>::Result UResult;
        typedef typename SignedIntFor<T>::Result   SResult;
        static  const    bool IsSignedType = IsSigned<T>::Value;
        typedef typename Pick<IsSignedType,SResult,UResult>::Type Result;
        typedef typename Result::Type Type;
        static  const    T            Minimum = Result::Minimum;
        static  const    T            Maximum = Result::Maximum;
    };




}

#endif

