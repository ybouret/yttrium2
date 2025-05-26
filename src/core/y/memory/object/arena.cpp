
#include "y/memory/object/arena.hpp"
#include "y/memory/object/chunk.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/object/book.hpp"
#include "y/core/utils.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        const char * const Arena:: CallSign = "Memory::Arena";

        void Arena:: releaseWorkspace() noexcept
        {
            assert(0==count);
            assert(0!=chunk);
            assert(capacity>0);
            assert(memSpace>0);
            assert(memShift>0);
            assert(0==acquiring);
            assert(0==releasing);

            book.store(memShift,chunk);
            memSpace = 0;
            memShift = 0;
            capacity = 0;
            Coerce(chunk) = 0;

        }


        void Arena:: releaseAllChunks() noexcept
        {
            assert(0!=chunk);
            assert(0!=acquiring);
            assert(0!=releasing);
            acquiring = releasing = 0;
            size_t missing = 0;
            while(count>0)
            {
                Chunk &current = chunk[--count];
                missing += current.userBlocks-current.freeBlocks;
                book.store(userShift,current.data);
                Memory::Stealth::Zero( &current, sizeof(Chunk) );
            }
            if(missing>0)
            {
                std::cerr << "*** " << CallSign << "[" << blockSize << "] missing #" << missing << std::endl;
            }
        }

        Arena:: ~Arena() noexcept
        {
            releaseAllChunks();
            releaseWorkspace();
        }

        Chunk * Arena:: makeInPlaceChunk(void * const addr)
        {
            assert(0!=addr);
            return new (addr) Chunk(book.query(userShift),numBlocks,blockSize);
        }



        Arena:: Arena(const size_t userBlockSize,
                      const size_t userPageBytes) :
        available(0),
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
            // sanity check
            assert(userShift>=book.MinPageShift);
            assert(userShift<=book.MaxPageShift);

            std::cerr << "for userBlockSize=" << userBlockSize << std::endl;
            std::cerr << "will allocate |chunk| = " << userBytes << " bytes" << std::endl;
            std::cerr << "blocks/chunk          = " << int(numBlocks) << std::endl;

            //------------------------------------------------------------------
            //
            //
            // first allocation : for workspace
            //
            //
            //------------------------------------------------------------------
            memSpace      = NextPowerOfTwo(Clamp(Book::MinPageBytes,userPageBytes,Book::MaxPageBytes),memShift);
            Coerce(chunk) = static_cast<Chunk *>(book.query(memShift));
            capacity      = memSpace / sizeof(Chunk);

            std::cerr << "memSpace=" << memSpace << " => capacity=" << capacity << " chunks per arena" << std::endl;

            //------------------------------------------------------------------
            //
            //
            // second allocation: create first chunk
            //
            //
            //------------------------------------------------------------------
            try {
                Coerce(chunk) = makeInPlaceChunk(chunk);
                assert(chunk->freeBlocks==numBlocks);
            }
            catch(...)
            {
                Coerce(chunk) = 0;
                releaseWorkspace();
                throw;
            }

            //------------------------------------------------------------------
            //
            //
            // update
            //
            //
            //------------------------------------------------------------------
            count      = 1;
            available  = numBlocks;
            acquiring  = releasing = chunk;

        }



    }

}

#include "y/exception.hpp"

namespace Yttrium
{
    namespace Memory
    {

        void Arena:: newChunkRequired()
        {
            assert(0==available);
            if(count<capacity)
            {
                acquiring = makeInPlaceChunk(chunk+count);
                ++count;
                available += numBlocks;
            }
            else
            {
                throw Exception("Need More Memory");
            }


        }

        void  * Arena:: acquire()
        {
            // find acquiring
            if(available>0)
            {
                if( acquiring->freeBlocks>0 )
                {
                    // cache
                }
                else
                {
                    throw Exception("ToDo");
                }
            }
            else
            {
                newChunkRequired();
            }

            assert(0!=acquiring);
            assert(0!=releasing);
            assert(available>0);
            assert(acquiring->freeBlocks>0);

            --available;
            return acquiring->acquire(blockSize);
        }

    }
}

