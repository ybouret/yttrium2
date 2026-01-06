#include "y/utest/run.hpp"

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




        class Alphabet
        {
        public:
            static const size_t              Codes = 256;
            static const Character::CodeType NYT   = Codes;
            static const Character::CodeType EOS   = NYT+1;

            explicit Alphabet();
            virtual ~Alphabet() noexcept;


        private:
            Y_Disable_Copy_And_Assign(Alphabet);
        };

    }
}

Y_UTEST(info_alphabet)
{

}
Y_UDONE()

