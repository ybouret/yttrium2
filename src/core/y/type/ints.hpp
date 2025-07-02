
//! \file

#ifndef Y_Type_Ints_Included
#define Y_Type_Ints_Included 1

#include "y/calculus/integer-log2.hpp"
#include "y/type/list.hpp"
#include "y/type/pick.hpp"
#include "y/type/is-signed.hpp"

namespace Yttrium
{
    template <typename T> struct UnsignedInt;


    //! Metrics for uint8_t
    template <>
    struct UnsignedInt<uint8_t>
    {
        typedef uint8_t   Type;           //!< alias
        static const Type Minimum = 0x00; //!< alias
        static const Type Maximum = 0xff; //!< alias
    };

    //! Metrics for uint16_t
    template <>
    struct UnsignedInt<uint16_t>
    {
        typedef uint16_t  Type;             //!< alias
        static const Type Minimum = 0x0000; //!< alias
        static const Type Maximum = 0xffff; //!< alias
    };

    //! Metrics for uint32_t
    template <>
    struct UnsignedInt<uint32_t>
    {
        typedef uint32_t  Type;                 //!< alias
        static const Type Minimum = 0x00000000; //!< alias
        static const Type Maximum = 0xffffffff; //!< alias
    };

    //! Metrics for uint64_t
    template <>
    struct UnsignedInt<uint64_t>
    {
        typedef uint64_t  Type;                            //!< alias
        static const Type Minimum = 0x0000000000000000ULL; //!< alias
        static const Type Maximum = 0xffffffffffffffffULL; //!< alias
    };

    //! Unsigned metrics
    /** \return list of unsigned metrics */
    typedef TL4(UnsignedInt<uint8_t>,
                UnsignedInt<uint16_t>,
                UnsignedInt<uint32_t>,
                UnsignedInt<uint64_t>) UnsignedInts;

    //! find corresponding unsigned metrics
    template <typename T>
    struct UnsignedIntFor
    {
        typedef typename TL::TypeAt<UnsignedInts,IntegerLog2For<T>::Value>::Result Result; //!< alias
    };



    template <typename T> struct SignedInt;

    //! Metrics for int8_t
    template <>
    struct SignedInt<int8_t>
    {
        typedef int8_t    Type;           //!< alias
        static const Type Minimum = -128; //!< alias
        static const Type Maximum =  127; //!< alias
    };

    //! Metrics for int16_t
    template <>
    struct SignedInt<int16_t>
    {
        typedef int16_t   Type;             //!< alias
        static const Type Minimum = -32768; //!< alias
        static const Type Maximum =  32767; //!< alias
    };


    //! Metrics for int32_t
    template <>
    struct SignedInt<int32_t>
    {
        typedef int32_t   Type;                      //!< alias
        static const Type Minimum = -2147483647L-1L; //!< alias
        static const Type Maximum =  2147483647L;    //!< alias
    };

    //! Metrics for int64_t
    template <>
    struct SignedInt<int64_t>
    {
        typedef int64_t    Type;                                 //!< alias
        static const Type  Minimum = -9223372036854775807LL-1LL; //!< alias
        static const Type  Maximum =  9223372036854775807LL;     //!< alias
    };


    //! Signed metrics
    /** \return list of unsigned metrics */
    typedef TL4(SignedInt<int8_t>,
                SignedInt<int16_t>,
                SignedInt<int32_t>,
                SignedInt<int64_t>) SignedInts;

    //! find corresponding signed metrics
    template <typename T>
    struct SignedIntFor
    {
        typedef typename TL::TypeAt<SignedInts,IntegerLog2For<T>::Value>::Result Result; //!< alias
    };



    //! gathering info for integral metrics
    template <typename T>
    struct IntegerFor
    {
        typedef typename UnsignedIntFor<T>::Result UResult;               //!< alias
        typedef typename SignedIntFor<T>::Result   SResult;               //!< alias
        static  const    bool IsSignedType = IsSigned<T>::Value;          //!< alias
        typedef typename Pick<IsSignedType,SResult,UResult>::Type Result; //!< alias
        typedef typename Result::Type Type;                               //!< alias
        static  const    T            Minimum = Result::Minimum;          //!< alias
        static  const    T            Maximum = Result::Maximum;          //!< alias
    };


    template <unsigned> struct UnsignedSizeOf;
    template <>         struct UnsignedSizeOf<1> { typedef uint8_t  Type; };
    template <>         struct UnsignedSizeOf<2> { typedef uint16_t Type; };
    template <>         struct UnsignedSizeOf<4> { typedef uint32_t Type; };
    template <>         struct UnsignedSizeOf<8> { typedef uint64_t Type; };

    template <unsigned> struct SignedSizeOf;
    template <>         struct SignedSizeOf<1> { typedef int8_t  Type; };
    template <>         struct SignedSizeOf<2> { typedef int16_t Type; };
    template <>         struct SignedSizeOf<4> { typedef int32_t Type; };
    template <>         struct SignedSizeOf<8> { typedef int64_t Type; };



}

#endif

