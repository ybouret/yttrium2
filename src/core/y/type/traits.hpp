//! \file
#ifndef Y_Type_Traits_Included
#define Y_Type_Traits_Included 1

#include "y/type/pick.hpp"
#include "y/type/list.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! default IsSameType
    //
    //__________________________________________________________________________
    template <class T, class U>
    struct IsSameType
    {
        enum { Value = false /*!< general case */ };
    };

    //__________________________________________________________________________
    //
    //
    //! specialized IsSameType
    //
    //__________________________________________________________________________
    template <class T>
    struct IsSameType<T,T>
    {
        enum { Value = true /*!< particular case */ }; 
    };

    namespace TL
    {
        typedef TL5(signed char, short, int, long, long long)                                       StandardIntegers; //!< standard signed
        typedef TL5(unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long) StandardUnsigned; //!< standard unsigned
        typedef TL4(uint8_t,uint16_t,uint32_t,uint64_t)                                             PlatformIntegers; //!< system unsigned
        typedef TL4(int8_t,int16_t,int32_t,int64_t)                                                 PlatformUnsigned; //!< system signed
        typedef TL2(bool,char)                                                                      LanguageIntegers; //!< misc. chart
        typedef TL3(float,double,long double)                                                       IsoFloatingPoint; //!< floating point
    }


    //__________________________________________________________________________
    //
    //
    //
    //! Computing Type Traits
    //
    //
    //__________________________________________________________________________
    template <typename T> class TypeTraits
    {
    public:
        typedef  T Type; //!< original type

    private:
        TypeTraits();  //!< disabled
        ~TypeTraits(); //!< disabled
        Y_Disable_Copy_And_Assign(TypeTraits); //!< disabled

        //______________________________________________________________________
        //
        //
        // Constness
        //
        //______________________________________________________________________
    private:
        template <class U> struct UnConst            { typedef U   Result; enum { Value = false }; };
        template <class U> struct UnConst<const U>   { typedef U   Result; enum { Value = true  }; };
        template <class U> struct UnConst<const U *> { typedef U * Result; enum { Value = true  }; };
        template <class U> struct UnConst<const U &> { typedef U & Result; enum { Value = true  }; };

    public:
        typedef typename UnConst<T>::Result    MutableType; /*!< non const 'T'      */
        enum { IsConst = UnConst<T>::Value                  /*!< true if T is const */ };

        //______________________________________________________________________
        //
        //
        // Volatility
        //
        //______________________________________________________________________
    private:
        template <class U> struct UnVolatile               { typedef U   Result; enum { Value = false }; };
        template <class U> struct UnVolatile<volatile U>   { typedef U   Result; enum { Value = true  }; };
        template <class U> struct UnVolatile<volatile U *> { typedef U * Result; enum { Value = true  }; };
        template <class U> struct UnVolatile<volatile U &> { typedef U & Result; enum { Value = true  }; };

    public:
        typedef typename UnVolatile<T>::Result SettledType; /*!< non volatile 'T'      */
        enum { IsVolatile = UnVolatile<T>::Value            /*!< true if T is volatile */};


        //______________________________________________________________________
        //
        //
        // Pointer
        //
        //______________________________________________________________________
    private:
        template <class U> struct PointerTraits      { enum { Value = false }; typedef NullType PointeeType; };
        template <class U> struct PointerTraits<U *> { enum { Value = true };  typedef U        PointeeType; };

    public:
        enum { IsPointer = PointerTraits<T>::Value                    /*!< true if 'T' can be written as 'U *'.      */ };
        typedef typename   PointerTraits<T>::PointeeType PointeeType; /*!< returns 'U' for 'U *', NullType otherwise.*/


        //______________________________________________________________________
        //
        //
        // Pointer To Member
        //
        //______________________________________________________________________
    private:
        template <class U>         struct PointerToMemberTraits         { enum { Value = false }; };
        template <class U,class V> struct PointerToMemberTraits<U V::*> { enum { Value = true  }; };

    public:
        enum { IsPointerToMember = PointerToMemberTraits<T>::Value /*!< true if 'T' is a pointer to member. */ };


        //______________________________________________________________________
        //
        //
        // Reference
        //
        //______________________________________________________________________
    private:
        template <class U> struct ReferenceTraits      { enum { Value = false }; typedef U ReferredType; };
        template <class U> struct ReferenceTraits<U &> { enum { Value = true  }; typedef U ReferredType; };

    public:
        enum { IsReference = ReferenceTraits<T>::Value /*!< true if 'T' can be written as 'U &'. */ };
        typedef typename ReferenceTraits<T>::ReferredType                  &ReferenceType;      //!< returns 'U &' for 'U &' and 'U'.
        typedef const typename ReferenceTraits<MutableType>::ReferredType  &ConstReferenceType; //!< returns 'const U &'.

        //______________________________________________________________________
        //
        //
        // IsArray
        //
        //______________________________________________________________________
    private:
        template <typename U>           struct ArrayTraits        { enum { Value = false }; typedef NullType Type; };
        template <typename U>           struct ArrayTraits<U []>  { enum { Value = true  }; typedef U        Type; };
        template <typename U, size_t N> struct ArrayTraits<U [N]> { enum { Value = true  }; typedef U        Type; };

    public:
        enum { IsArray = ArrayTraits<T>::Value };

        //! true if T if ITEM [] of ITEM[N]
        template <typename ITEM> struct IsArrayOf {
            enum { Value = IsArray && IsSameType<ITEM, typename ArrayTraits<T>::Type>::Value } ;
        };

    public:
        enum { InStandardIntegers   = ( TL::IndexOf<TL::StandardIntegers,T>::Value >= 0 ) };
        enum { InStandardUnsigned   = ( TL::IndexOf<TL::StandardUnsigned,T>::Value >= 0 ) };
        enum { InPlatformIntegers   = ( TL::IndexOf<TL::PlatformIntegers,T>::Value >= 0 ) };
        enum { InPlatformUnsigned   = ( TL::IndexOf<TL::PlatformUnsigned,T>::Value >= 0 ) };
        enum { InLanguageIntegers   = ( TL::IndexOf<TL::LanguageIntegers,T>::Value >= 0 ) };
        enum { IsIsoFloatingPoint   = ( TL::IndexOf<TL::IsoFloatingPoint,T>::Value >= 0 ) };
        enum { IsIntegral           = (InStandardIntegers || InStandardUnsigned || InPlatformIntegers ||InPlatformUnsigned || InLanguageIntegers) };
        enum { IsArithmetic         = (IsIntegral || IsIsoFloatingPoint) };
        enum { IsFundamental        = (IsArithmetic  || IsSameType<T,void>::Value) };
        enum { IsPointingTo         = (IsPointer     || IsPointerToMember) };
        enum { IsPrimitive          = (IsFundamental || IsPointingTo) };

        typedef typename
        Pick<IsReference,          // T is 'U &' or 'const U &' ?
        T                          // true => parameter is T
        ,                          //
                                   // false =>
        typename Pick<IsPrimitive, //     T is primitive 'U' or 'const U'
        T,                         //     true => return T
        ConstReferenceType>:: Type //     false => return const reference
        > :: Type ParamType;       //!< this is the resulting type

        
    };

}


#endif

