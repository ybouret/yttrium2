
//! \file

#ifndef Y_Hexadecimal_Included
#define Y_Hexadecimal_Included 1

#include "y/ability/legacy-string.hpp"
#include "y/ascii/cases.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/ints.hpp"
#include "y/type/explanation.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Hexadecimal to string representation
    //
    //
    //__________________________________________________________________________
    class Hexadecimal : public LegacyString
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char     Header[2];                                                      //!< '0x'
        static const unsigned HeaderSize    = sizeof(Header);                                 //!< alias
        static const unsigned MaxOutputSize = HeaderSize + sizeof(uint64_t) * 2;              //!< alias
        static const unsigned RequiredChars = MaxOutputSize+1;                                //!< for final '\0';
        static const unsigned InternalChars = Alignment::On<2>::CeilOf<RequiredChars>::Value; //!< alias

        static const char     LowerChar[16];       //!< ['0'..'f']
        static const char     UpperChar[16];       //!< ['0'..'F']
        static const char     LowerByte[256][4];   //!< [ "00".."ff" ]
        static const char     UpperByte[256][4];   //!< [ "00".."FF"]

        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________

        //! cleanup
        virtual ~Hexadecimal() noexcept;

        //! duplicate
        Hexadecimal(const Hexadecimal &) noexcept;

        //! default to 0
        Hexadecimal() noexcept;

        //! transform integral type to hexadecimal string
        /**
         \param v any integral value
         \param explanation for type of formatting
         */
        template <typename V> inline
        Hexadecimal(const V &v, const Explanation explanation = Diffuse) : array()
        {
            typedef typename UnsignedIntFor<V>::Result::Type U;
            union {
                V data;
                U word;
            } alias = { v };
            prolog();
            format(alias.word);
            epilog(explanation);
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * c_str() const noexcept;

    private:
        Y_Disable_Assign(Hexadecimal);           //!< discarding
        char array[InternalChars];               //!< internal array of chats
        void clear() noexcept;                   //!< clear all
        void prolog() noexcept;                  //!< clear and print header
        void format(const uint8_t  &)  noexcept; //!< format
        void format(const uint16_t &)  noexcept; //!< format
        void format(const uint32_t &)  noexcept; //!< format
        void format(const uint64_t &)  noexcept; //!< format
        void epilog(const Explanation) noexcept; //!< make concise if necessary


    };


}

#endif
