
#include "y/jive/context.hpp"
#include "y/format/decimal.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Context:: ~Context() noexcept
        {

        }

        Context:: Context(const Tag &t) noexcept :
        tag(t),
        line(1),
        column(1)
        {
        }

        Context:: Context(const Context &ctx) noexcept :
        tag(ctx.tag),
        line(ctx.line),
        column(ctx.column)
        {
        }

        String Context::str() const
        {
            return Formatted::Get("%s:%s:%s:", tag->c_str(), Decimal(line).c_str(), Decimal(column).c_str());
        }

        Context & Context:: dot() noexcept
        {
            ++Coerce(column);
            return *this;
        }

        Context & Context:: endl() noexcept
        {
            ++Coerce(line);
            Coerce(column)=1;
            return *this;
        }

    }

}

