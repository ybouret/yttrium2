
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


            Unit:: Unit(const Unit & _) :
            Object(),
            Context(_),
            Token(_),
            name(_.name),
            next(0),
            prev(0)
            {
            }


        }

    }

}
