
#include "y/information/iobit.hpp"

namespace Yttrium
{
    namespace Information
    {

        IOBit:: IOBit(ParamType a) noexcept :
        next(0),
        prev(0),
        code(a)
        {
        }

        IOBit:: ~IOBit() noexcept
        {

        }

        IOBit:: IOBit(const IOBit &ch) noexcept :
        next(0),
        prev(0),
        code(ch.code)
        {}

        const char * const IOBit:: CallSign = "IOBit";


        IOBit::ConstType & IOBit:: operator*() const noexcept { return code; }
        IOBit::Type      & IOBit:: operator*()       noexcept { return code; }

    }

}

#include "y/concurrent/data/inventory.hpp"


namespace Yttrium
{
    namespace Information
    {
        IOBit::Cache  & IOBit:: CacheInstance()
        {
            static Cache &cache = Concurrent::Inventory<IOBit>::Instance();
            return cache;
        }


    }
}

