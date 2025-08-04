

#include "y/jive/pattern/logic.hpp"
#include "y/system/exception.hpp"
#include "y/stream/output.hpp"
#include "y/jive/pattern/basic/all.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Logic:: ~Logic() noexcept
        {

        }

        Logic:: Logic(const uint32_t t) noexcept :
        Pattern(t),
        Patterns()
        {
        }


        Logic:: Logic(const Logic &L) :
        Pattern(L),
        Patterns(L)
        {
        }



        OutputStream & Logic:: lnk(OutputStream &fp) const
        {
            for(const Pattern *op = head;op; op=op->next)
                Endl( to(op,op->viz(fp)) );
            return fp;
        }

        Logic & Logic:: operator<<(Pattern * const p) noexcept
        {
            assert(0!=p);
            pushTail(p);
            return *this;
        }

        Logic & Logic:: add(const uint8_t c)
        {
            pushTail( new Byte(c) );
            return *this;
        }

        Logic & Logic:: add(const uint8_t a, const uint8_t b)
        {
            pushTail( new Range(a,b) );
            return *this;
        }

        size_t Logic:: srz(OutputStream &fp) const
        {
            size_t res = 0;
            for(const Pattern *op=head;op;op=op->next)
            {
                res += op->serialize(fp);
            }
            return res;
        }

        


    }

}

