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

        enum Category
        {
            Streaming=1, //!< +NYT, -EOS
            Messaging=2  //!< +NYT, +EOS
        };

        class Character
        {
        public:
            typedef uint16_t DataType; //!< alias for bytes + control
            typedef uint32_t FreqType; //!< alias
            typedef uint64_t CodeType; //!< alias

            const DataType data;
            CodeType       code;
            unsigned       bits;
            FreqType       freq;
            Character *    next;
            Character *    prev;

        private:
            Y_Disable_Copy_And_Assign(Character);
            Character();
            ~Character() noexcept;
        };


        class Alphabet
        {
        public:
            typedef Character::DataType DataType;
            typedef Character::FreqType FreqType;
            typedef Character::CodeType CodeType;

            static const DataType Chars = 256;
            static const DataType NYT   = Chars;
            static const DataType EOS   = NYT+1;


            explicit Alphabet(const Category);
            virtual ~Alphabet() noexcept;

            const Category    category;
            const DataType    universe;
            const DataType    detected;
            const FreqType    totality;
            Character * const character;
            
        private:
            Y_Disable_Copy_And_Assign(Alphabet);


        };

        Alphabet:: Alphabet(const Category c) :
        category(c),
        universe(Chars+category),
        detected(0),
        totality(0),
        character(0)
        {

        }

        Alphabet:: ~Alphabet() noexcept
        {
        }



    }
}

Y_UTEST(info_alphabet)
{

}
Y_UDONE()

