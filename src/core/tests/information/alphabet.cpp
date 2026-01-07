#include "y/utest/run.hpp"

#include "y/object.hpp"
#include "y/memory/allocator.hpp"
#include "y/ostream-proto.hpp"
#include <cstring>
#include "y/ascii/printable.hpp"

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


            Character(const CodeType, const size_t) noexcept;
            Y_OSTREAM_PROTO(Character);

            const CodeType code; //!< original character
            Frequency      freq;
            CodeType       data;
            size_t         bits;

        private:
            Y_Disable_Copy_And_Assign(Character);
            ~Character() noexcept;
        };

        Character:: Character(const CodeType c, const size_t n) noexcept :
        code(c),
        freq(0),
        data(c),
        bits(n)
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

            void display(std::ostream &) const;


            const Category     category; //!< communication mode
            const CodeType     universe; //!< Codes+[1=Streaming|2=Messaging]
        protected:
            CodeType           detected; //!< 0..Codes
            Character * const  character;

        private:
            Y_Disable_Copy_And_Assign(Alphabet);
            size_t wlen;
            void * wksp;

            void setup() noexcept;

        };

        std::ostream & operator<<(std::ostream &os, const Character &ch)
        {
            static const Character::CodeType one = 1;
            switch(ch.code)
            {
                case Alphabet::NYT: os << "NYT "; break;
                case Alphabet::EOS: os << "EOS "; break;
                default:
                    assert(ch.code<256);
                    os << std::setw(4) << ASCII::Printable::Char[ch.code];
                    break;
            }
            os << ": #" << std::setw(2) << ch.bits << ": ";
            for(size_t i=ch.bits;i>0;--i)
            {
                if( ch.data & (one<<(i-1))) os << '1'; else os << '0';
            }

            return os;
        }

        Alphabet:: Alphabet(const Category m) :
        category(m),
        universe( Codes + category ),
        detected(0),
        character(0),
        wlen( sizeof(Character) * universe ),
        wksp( Object::AllocatorInstance().acquire(wlen) )
        {
            Coerce(character) = static_cast<Character *>(wksp);
            setup();
        }

        Alphabet:: ~Alphabet() noexcept
        {
            Coerce(character) = 0;
            memset(wksp,0,wlen);
            Object::AllocatorLocation().release(wksp,wlen);
        }

        void Alphabet:: setup() noexcept
        {
            for(CodeType i=0;i<Codes;++i)
                new (character+i) Character(i,8);
            for(CodeType i=Codes;i<universe;++i)
                new (character+i) Character(i,9);
        }

        void Alphabet:: display(std::ostream &os) const
        {
            for(CodeType i=0;i<Codes;++i)
            {
                os << character[i] << std::endl;
            }

            if(detected<Codes)
            {
                os << character[NYT] << std::endl;
            }

            if(Messaging==category)
                os << character[EOS] << std::endl;

        }



    }
}

Y_UTEST(info_alphabet)
{
    Y_SIZEOF(Information::Character);
    Y_SIZEOF(Information::Alphabet);

    Information::Alphabet streaming(Information::Streaming);
    Information::Alphabet messaging(Information::Messaging);

    streaming.display(std::cerr);
    messaging.display(std::cerr);


}
Y_UDONE()

