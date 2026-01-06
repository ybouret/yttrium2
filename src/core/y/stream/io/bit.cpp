
#include "y/stream/io/bit.hpp"

namespace Yttrium
{
    namespace IO
    {

        Bit:: Bit(ParamType a) noexcept :
        next(0),
        prev(0),
        code(a)
        {
        }

        Bit:: ~Bit() noexcept
        {

        }

        Bit:: Bit(const Bit &ch) noexcept :
        next(0),
        prev(0),
        code(ch.code)
        {}

        const char * const Bit:: CallSign = "IO::Bits";


        Bit::ConstType & Bit:: operator*() const noexcept { return code; }
        Bit::Type      & Bit:: operator*()       noexcept { return code; }

    }

}

#include "y/concurrent/data/inventory.hpp"


namespace Yttrium
{
    namespace IO
    {
        Bit::Cache  & Bit:: CacheInstance()
        {
            static Cache &cache = Concurrent::Inventory<Bit>::Instance();
            return cache;
        }


    }
}

