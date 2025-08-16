#include "y/concurrent/api/context.hpp"
#include "y/format/decimal.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        Context:: ~Context() noexcept
        {
        }

        Context:: Context(Lockable &   ll,
                          const size_t sz,
                          const size_t rk) noexcept:
        sync(ll),
        size(sz),
        rank(rk),
        indx(rank+1)
        {
            assert(size>0);
            assert(rank<size);
        }

        std::ostream & operator<<(std::ostream &os, const Context &ctx)
        {
            return os << Decimal(ctx.size) << '.' << Decimal(ctx.indx);
        }
    }

}

