
#include "y/container/htable.hpp"
#include "y/utest/run.hpp"
#include "y/check/crc32.hpp"

using namespace Yttrium;

namespace
{
    static inline bool Same(const void * const lhs, const void * const rhs) noexcept
    {
        return *(const int *)lhs == *(const int *)rhs;
    }
}
Y_UTEST(container_htable)
{

    HTable table;

    int           arr[4] = { 1, 2, 3, 4 };
    const size_t  key[4] = { CRC32::Run(arr[0]), CRC32::Run(arr[1], CRC32::Run(arr[2], CRC32::Run(arr[3]))) };

    for(size_t i=0;i<4;++i)
    {
        Y_CHECK( table.insert(key[i], &arr[i], Same) );
    }

    for(size_t i=0;i<4;++i)
    {
        Y_CHECK( table.remove(key[i], &arr[i], Same) );
    }

    for(size_t i=0;i<4;++i)
    {
        Y_CHECK( table.insert(key[i], &arr[i], Same) );
    }

    for(size_t i=0;i<4;++i)
    {
        Y_CHECK( !table.insert(key[i], &arr[i], Same) );
    }

    table.free();

}
Y_UDONE()

