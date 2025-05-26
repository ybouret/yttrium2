
#include "y/memory/object/arena.hpp"
#include "y/memory/object/chunk.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/object/book.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Memory
    {

        Arena:: ~Arena() noexcept
        {
        }


        Arena:: Arena(const size_t userBlockSize,
                      const size_t userPageBytes) :
        chunk(0),
        count(0),
        capacity(0),
        memSpace(0),
        memShift(0),
        blockSize(userBlockSize),
        userShift(0),
        numBlocks(0),
        userBytes( Chunk::UserBytesFor(blockSize, userPageBytes, Coerce(userShift), Coerce(numBlocks))),
        book( Book::Instance() )
        {
            assert(userShift>=book.MinPageShift);
            assert(userShift<=book.MaxPageShift);



            // first allocation for chunks
            memSpace = NextPowerOfTwo(Clamp(Book::MinPageBytes,userPageBytes,Book::MaxPageBytes),memShift);
            Coerce(chunk) = static_cast<Chunk *>(book.query(memShift));
            capacity = memSpace / sizeof(Chunk);

        }
    }

}

