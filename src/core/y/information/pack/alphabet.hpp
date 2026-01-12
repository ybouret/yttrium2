

//! \file

#ifndef Y_Information_Pack_Alphabet_Included
#define Y_Information_Pack_Alphabet_Included 1

#include "y/information/pack/category.hpp"
#include "y/information/pack/character.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            class Alphabet
            {
            public:
                typedef Character::DataType  DataType;
                typedef Character::FreqType  FreqType;
                typedef Character::CodeType  CodeType;
                typedef RawListOf<Character> CharList;

                static const DataType Chars = 256;
                static const DataType NYT   = Chars; //!< with 0 freq
                static const DataType EOS   = NYT+1; //!< with 0 freq
                static const FreqType MaxFreq = IntegerFor<FreqType>::Maximum;

                explicit Alphabet(const Category);
                virtual ~Alphabet() noexcept;

                Alphabet & operator<<(const uint8_t) noexcept;

                void display(std::ostream &) const;
                void reduce() noexcept;


                const Category    category;
                const DataType    universe;
                DataType          detected;   //!< up to Codes to remove NYT
                FreqType          totality;   //!< current sum of frequencies
                CharList          encoding;   //!< encoding chars + control
            private:
                size_t            ch_count;
                size_t            ch_bytes;
            public:
                Character * const database;   //!< database
                Character * const nyt;
                Character * const eos;

            private:
                Y_Disable_Copy_And_Assign(Alphabet);




                void setup() noexcept; //!< initial setup on a clean workspace
                void reset() noexcept; //!< reset all
                void cntrl() noexcept; //!< register controls in encoding

            };


           

           
        }

    }

}

#endif // !Y_Information_Pack_Alphabet_Included

