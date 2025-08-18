
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
        column(0)
        {
        }

        Context:: Context(const Context &ctx) noexcept :
        tag(ctx.tag),
        line(ctx.line),
        column(ctx.column)
        {
        }

        namespace {
            static const char fmt[] ="%s:%s:%s:";
#define     Y_Jive_Ctx fmt,tag->c_str(), Decimal(line).c_str(), Decimal(column).c_str()
        }
        String Context::str() const
        {
            return Formatted::Get(Y_Jive_Ctx);
        }

        void Context:: stamp(Exception &excp) const
        {
            excp.pre(Y_Jive_Ctx);
        }


        Context & Context:: dot() noexcept
        {
            ++Coerce(column);
            return *this;
        }

        Context & Context:: endl() noexcept
        {
            ++Coerce(line);
            Coerce(column)=0;
            return *this;
        }

    }

}

