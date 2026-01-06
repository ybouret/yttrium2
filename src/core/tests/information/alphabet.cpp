#include "y/utest/run.hpp"

#include "y/object.hpp"
#include "y/memory/allocator.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace  Information
    {



        class Character
        {
        public:
            typedef uint32_t Frequency;
            typedef uint32_t CodeType;

            Character(const CodeType) noexcept;

            const CodeType code;
            Frequency      freq;

        private:
            Y_Disable_Copy_And_Assign(Character);
            ~Character() noexcept;
        };

        Character:: Character(const CodeType ch) noexcept :
        code(ch), freq(0)
        {
        }

        enum Category
        {
            Streaming=1, //!< no  EOS
            Messaging=2  //!< use EOS
        };


        class Alphabet
        {
        public:
            typedef Character::CodeType      CodeType;
            static const size_t   Codes = 256;
            static const CodeType NYT   = Codes;
            static const CodeType EOS   = NYT+1;



            explicit Alphabet(const Category);
            virtual ~Alphabet() noexcept;

            const Category     category;     //!< communication mode
            const CodeType     universe; //!< Codes+[1=Streaming|2=Messaging]
        protected:
            CodeType           detected; //!< 0..Codes
            Character * const  character;

        private:
            Y_Disable_Copy_And_Assign(Alphabet);
            size_t wlen;
            void * wksp;
        };



        Alphabet:: Alphabet(const Category m) :
        category(m),
        universe( Codes + category ),
        detected(0),
        character(0),
        wlen( sizeof(Character) * universe ),
        wksp( Object::AllocatorInstance().acquire(wlen) )
        {
            Coerce(character) = static_cast<Character *>(wksp);
            for(CodeType i=0;i<universe;++i)
                new (character+i) Character(i);
        }

        Alphabet:: ~Alphabet() noexcept
        {
            Coerce(character) = 0;
            memset(wksp,0,wlen);
            Object::AllocatorLocation().release(wksp,wlen);
        }


    }
}

Y_UTEST(info_alphabet)
{
    Y_SIZEOF(Information::Character);
    Y_SIZEOF(Information::Alphabet);

    Information::Alphabet streaming(Information::Streaming);
    Information::Alphabet messaging(Information::Messaging);


}
Y_UDONE()

