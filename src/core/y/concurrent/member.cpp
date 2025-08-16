
#include "y/concurrent/member.hpp"
#include "y/format/decimal.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        Member:: ~Member() noexcept
        {
        }

        Member:: Member(const size_t sz,
                        const size_t rk) noexcept:
        size(sz),
        rank(rk),
        indx(rank+1)
        {
            assert(size>0);
            assert(rank<size);
        }

        std::ostream & operator<<(std::ostream &os, const Member &ctx)
        {
            return os << Decimal(ctx.size) << '.' << Decimal(ctx.indx);
        }
    }

}

