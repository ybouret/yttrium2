
#include "y/memory/object/arena.hpp"
//#include "y/system/exception.hpp"
#include "y/memory/object/chunk.hpp"
#include "y/memory/allocator/dyadic.hpp"

namespace Yttrium
{
    namespace Memory
    {

        Arena:: ~Arena() noexcept
        {
        }


        Arena:: Arena(const size_t userBlockSize,
                      const size_t userPageBytes) :
        blockSize(userBlockSize),
        userShift(0),
        numBlocks(0),
        userBytes( Chunk::UserBytesFor(blockSize, userPageBytes, Coerce(userShift), Coerce(numBlocks)))
        {

        }
    }

}

