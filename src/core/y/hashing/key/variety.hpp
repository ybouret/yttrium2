//! \file

#ifndef Y_Associative_Key_Variety_Included
#define Y_Associative_Key_Variety_Included 1

#include "y/type/traits.hpp"
#include "y/type/conversion.hpp"
#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{

    template <typename> class Complex;
    template <typename> class V2D;
    template <typename> class V3D;
    template <typename> class V4D;
    template <typename> class XReal;


    //__________________________________________________________________________
    //
    //
    //
    //! classification of keys
    //
    //
    //__________________________________________________________________________
    struct KeyVariety
    {
        //______________________________________________________________________
        //
        //
        //! Possible outcomes
        //
        //______________________________________________________________________
        enum Type
        {
            IsNotAvailable,
            IsMemoryBuffer,
            IsIntegralType,
            IsLegacyString
        };

        //______________________________________________________________________
        //
        //! helper
        //______________________________________________________________________
        static const char *Type2Text(const Type) noexcept;

        //______________________________________________________________________
        //
        //
        //! Making a sieve of possibilites
        //
        //______________________________________________________________________
        template <typename KEY>
        struct Cull
        {
        private:
            template <class U>    struct IsCompoundTrait               { enum { Value = false }; };
            template <typename Z> struct IsCompoundTrait< V2D<Z> >     { enum { Value = true };  };
            template <typename Z> struct IsCompoundTrait< V3D<Z> >     { enum { Value = true };  };
            template <typename Z> struct IsCompoundTrait< V4D<Z> >     { enum { Value = true };  };
            template <typename Z> struct IsCompoundTrait< Complex<Z> > { enum { Value = true };  };
            template <typename Z> struct IsCompoundTrait< XReal<Z> >   { enum { Value = true };  };

        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename TypeTraits<KEY>::MutableType MutableKey; //!< alias
            enum { IsCompound = IsCompoundTrait<MutableKey>::Value };
            static const bool _IsMemoryBuffer = Y_Is_SuperSubClass(Memory::ReadOnlyBuffer,MutableKey);   //!< inheritance
            static const bool _IsCharPointer_ = IsSameType<MutableKey,char *>::Value;                    //!< partial test
            static const bool _IsCharTableau_ = TypeTraits<MutableKey>::template IsArrayOf<char>::Value; //!< partial test
            static const bool _IsLegacyString = _IsCharPointer_ || _IsCharTableau_;                      //!< test for C-string
            static const bool _IsIntegralType = TypeTraits<MutableKey>::IsPrimitive || IsCompound;       //!< other acceptabe

            //__________________________________________________________________
            //
            //
            //! evaluate type with precedence of LegacyString over IntegralType
            //
            //__________________________________________________________________
            static const Type Kind =
            (   _IsLegacyString ? IsLegacyString :
             (  _IsIntegralType ? IsIntegralType :
              ( _IsMemoryBuffer ? IsMemoryBuffer : IsNotAvailable)));
        };


        typedef IntToType<IsIntegralType> IntegralType; //!< alias
        typedef IntToType<IsLegacyString> LegacyString; //!< alias
        typedef IntToType<IsMemoryBuffer> MemoryBuffer; //!< alias


    };

}

#endif
