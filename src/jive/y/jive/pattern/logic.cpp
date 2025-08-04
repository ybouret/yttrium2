

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


        void Logic:: vizLink(OutputStream &fp) const
        {
            for(const Pattern *op = ops.head;op; op=op->next)
                Endl( to(op,fp) );
        }

        Logic & Logic:: operator<<(Pattern * const p) noexcept
        {
            assert(0!=p);
            ops.pushTail(p);
            return *this;
        }


    }

}

