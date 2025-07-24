#include "y/hashing/digest.hpp"
#include "y/object/school-of.hpp"

#include "y/format/hexadecimal.hpp"
#include "y/type/destroy.hpp"

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
            if(code) Destroy(code);
        }


        const void * Digest:: ro() const noexcept
        {
            assert(code); return code->entry;
        }

        size_t Digest:: length() const noexcept
        {
            assert(code); return code->width;
        }

        size_t Digest:: size() const noexcept
        {
            assert(code); return code->width;
        }

        const uint8_t & Digest:: getItemAt(const size_t indx) const  noexcept
        {
            assert(code);
            assert(indx>0);
            assert(indx<=code->width);
            return code->cxx[indx];
        }


        String Digest:: str() const noexcept
        {
            assert(code);
            String s(WithAtLeast,code->width<<1,false);
            const uint8_t *p = code->entry;
            for(size_t i=code->width;i>0;--i)
            {
                s += Hexadecimal::LowerByte[ *(p++) ];
            }
            return s;
        }

        std::ostream & operator<<(std::ostream &os, const Digest &d)
        {
            return os << d.str();
        }
    }
}
