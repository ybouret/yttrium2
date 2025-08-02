
#include "y/jive/char.hpp"

namespace Yttrium
{
    namespace Jive
    {
        const char * const Char:: CallSign = "Jive::Char";

        Char:: ~Char() noexcept
        {
        }

        Char:: Char(const Char &c) noexcept :
        Context(c),
        next(0),
        prev(0),
        code(c.code)
        {

        }

        Char:: Char(ParamType c, const Context &ctx) noexcept :
        Context(ctx),
        next(0),
        prev(0),
        code(c)
        {
        }


    }

}

#include "y/concurrent/data/inventory.hpp"


namespace Yttrium
{
    namespace Jive
    {
        Char::Cache  & Char:: CacheInstance()
        {
            static Cache &cache = Concurrent::Inventory<Char>::Instance();
            return cache;
        }


    }
}
