#include "y/stream/io/char.hpp"

namespace Yttrium
{
    namespace IO
    {


        Char:: Char(const Type a) noexcept :
        next(0),
        prev(0),
        code(a)
        {
        }

        Char:: ~Char() noexcept
        {
            
        }

        Char:: Char(const Char &ch) noexcept :
        next(0),
        prev(0),
        code(ch.code)
        {}

        const char * const Char:: CallSign = "IO::Char";
        
    }

}

#include "y/concurrent/data/inventory.hpp"


namespace Yttrium
{
    namespace IO
    {
        Char::Cache  & Char:: CacheInstance()
        {
            static Cache &cache = Concurrent::Inventory<Char>::Instance();
            return cache;
        }


    }
}

