

//! \file

#ifndef Y_Information_Pack_Alphabet_Included
#define Y_Information_Pack_Alphabet_Included 1

#include "y/information/pack/category.hpp"
#include "y/information/pack/character.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/type/ints.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace IO { class Bits; }

    namespace Information
    {
        namespace Pack
        {
            //__________________________________________________________________
            //
            //
            //
            //! incremental alphabet
            //
            //
            //__________________________________________________________________
            class Alphabet
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Character::DataType  DataType; //!< alias
                typedef Character::FreqType  FreqType; //!< alias
                typedef Character::CodeType  CodeType; //!< alias
                typedef RawListOf<Character> CharList; //!< alias

                static const DataType Chars      = 256;                                    //!< data cjars
                static const DataType NYT        = Chars;                                  //!< with 0 freq
                static const DataType EOS        = NYT+1;                                  //!< with 0 freq
                static const FreqType MaxFreq    = IntegerFor<FreqType>::Maximum;          //!< max frequency
                static const size_t   SizeOfChar = sizeof(Character);                      //!< alias
                static const size_t   InnerChars = 1 + EOS;                                //!< data+cntl
                static const size_t   InnerBytes = InnerChars * SizeOfChar;                //!< local memory
                static const size_t   InnerWords = Alignment::WordsGEQ<InnerBytes>::Count; //!< local words

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Alphabet(const Category); //!< setup for a given categoru
                virtual ~Alphabet() noexcept;      //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return updated with single byte
                Alphabet & operator<<(const uint8_t) noexcept;

                void display(std::ostream &) const; //!< display status
                void reduce()             noexcept; //!< reduce entropy
                void reset()              noexcept; //!< reset all

                void emit(IO::Bits &bits, const uint8_t byte, IO::Bits &pool) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Category    category;   //!< usage
                const DataType    universe;   //!< depending on usage
                bool              writeNYT;   //!< monitoring need for NYT
                DataType          detected;   //!< up to Codes to remove NYT
                FreqType          totality;   //!< current sum of frequencies
                CharList          encoding;   //!< encoding chars + control
                
            public:
                Character * const database;   //!< database
                Character * const nyt;        //!< NYT location
                Character * const eos;        //!< EOS location

            private:
                Y_Disable_Copy_And_Assign(Alphabet); //!< discarding
                void * wksp[InnerWords];             //!< inner memory

                void emit(IO::Bits &bits, const Character &ch, IO::Bits &pool) const;
                void setup() noexcept; //!< initial setup on a clean workspace
                void cntrl() noexcept; //!< register controls in encoding

            };


           

           
        }

    }

}

#endif // !Y_Information_Pack_Alphabet_Included

