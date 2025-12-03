
#include "y/concurrent/member.hpp"
#include "y/format/decimal.hpp"
#include <cassert>
#include <iostream>
#include <cstring>

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

        String Member:: name() const
        {
            const Decimal      sd(size);
            const char * const sds = sd.c_str();
            const size_t       sdl = strlen( sds );
            const Decimal      id(indx);
            const char * const ids = id.c_str();
            const size_t       idl = strlen( ids ); assert(idl<=sdl);

            String res(sds,sdl);
            res += '.';
            for(size_t i=sdl-idl;i>0;--i) res += '0';
            res += String(ids,idl);
            return res;

        }

        std::ostream & operator<<(std::ostream &os, const Member &ctx)
        {
            return os << Decimal(ctx.size) << '.' << Decimal(ctx.indx);
        }


    }

}

