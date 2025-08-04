

#include "y/jive/pattern/logic.hpp"
#include "y/system/exception.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Logic:: ~Logic() noexcept
        {

        }

        Logic:: Logic(const uint32_t t) noexcept :
        Pattern(t),
        BaseType(),
        ops()
        {
        }


        Logic:: Logic(const Logic &L) :
        Pattern(L),
        BaseType(),
        ops(L.ops)
        {
        }

        Y_Ingress_Impl(Logic,ops)


        OutputStream & Logic:: lnk(OutputStream &fp) const
        {
            for(const Pattern *op = ops.head;op; op=op->next)
                Endl( to(op,op->viz(fp)) );
            return fp;
        }

        Logic & Logic:: operator<<(Pattern * const p) noexcept
        {
            assert(0!=p);
            ops.pushTail(p);
            return *this;
        }

        size_t Logic:: srz(OutputStream &fp) const
        {
            size_t res = 0;
            for(const Pattern *op = ops.head;op;op=op->next)
            {
                res += op->serialize(fp);
            }
            return res;
        }


    }

}

