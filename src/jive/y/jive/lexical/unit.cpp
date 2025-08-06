
#include "y/jive/lexical/unit.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            Unit:: ~Unit() noexcept {}

            Unit:: Unit(const Tag &uid, const Context &ctx) noexcept :
            Object(),
            Context(ctx),
            Token(),
            name(uid),
            next(0),
            prev(0)
            {
            }

            Unit::Unit(const Tag &uid, const Context &ctx, Token &tkn) noexcept :
            Object(),
            Context(ctx),
            Token(),
            name(uid),
            next(0),
            prev(0)
            {
                swapListFor(tkn);
            }


            Unit:: Unit(const Unit & _) :
            Object(),
            Context(_),
            Token(_),
            name(_.name),
            next(0),
            prev(0)
            {
            }

            std::ostream & operator<<(std::ostream &os, const Unit &unit)
            {
                os << unit.name;
                if(unit.size) {
                    const Token &self = unit;
                    os << "='" << self << "'";
                }
                return os;
            }

        }

    }

}
