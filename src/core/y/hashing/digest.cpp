#include "y/hashing/digest.hpp"
#include "y/object/school-of.hpp"

#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    namespace Hashing
    {

        class Digest::Code : public Object, public Memory::SchoolOf<uint8_t>
        {
        public:
            inline explicit Code(const size_t n) :
            Object(),
            Memory::SchoolOf<uint8_t>(n),
            width(n)
            {
                assert(width>0);
            }

            inline virtual ~Code() noexcept
            {

            }

            const size_t width;

        private:
            Y_Disable_Assign(Code);
        };

        Digest:: Digest(const size_t width) :
        code( new Code(width) )
        {
        }

        Digest:: ~Digest() noexcept
        {
        }


    }
}
