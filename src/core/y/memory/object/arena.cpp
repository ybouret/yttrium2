
#include "y/memory/object/arena.hpp"
#include "y/memory/object/chunk.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/object/book.hpp"
#include "y/core/utils.hpp"
#include "y/check/static.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        const char * const Arena:: CallSign = "Memory::Arena";

#define Y_Arena_Check(EXPR) do { if ( !(EXPR) ) { std::cerr << "*** " << #EXPR << std::endl;  return false; } } while(false)

        bool Arena:: isValid() const noexcept
        {
            Y_Arena_Check(0!=workspace);
            Y_Arena_Check(count<=capacity);
            Y_Arena_Check(workspace+capacity==endChunk);
            Y_Arena_Check(0!=acquiring);
            Y_Arena_Check(acquiring>=workspace);
            Y_Arena_Check(acquiring<endChunk);
            Y_Arena_Check(0!=releasing);
            Y_Arena_Check(releasing>=workspace);
            Y_Arena_Check(releasing<endChunk);

            for(size_t i=0,j=1;j<count;++i,++j)
            {
                const Chunk & lhs = workspace[i];
                const Chunk & rhs = workspace[j];
                Y_Arena_Check(lhs.data<rhs.data);
            }

            return true;
        }


        void Arena:: releaseWorkspace() noexcept
        {
            assert(0==count);
            assert(0!=workspace);
            assert(capacity>0);
            assert(memBytes>0);
            assert(memShift>0);
            assert(0==acquiring);
            assert(0==releasing);

            book.store(memShift,workspace);
            memBytes  = 0;
            memShift  = 0;
            capacity  = 0;
            workspace = 0;
            endChunk  = 0;
        }


        void Arena:: releaseAllChunks() noexcept
        {
            assert( isValid() );
            acquiring = releasing = 0;
            size_t missing = 0;
            while(count>0)
            {
                Chunk &current = workspace[--count];
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
        acquiring(0),
        releasing(0),
        workspace(0),
        count(0),
        capacity(0),
        endChunk(0),
        memBytes(0),
        memShift(0),
        blockSize(userBlockSize),
        userShift(0),
        numBlocks(0),
        userBytes( Chunk::UserBytesFor(blockSize, userPageBytes, Coerce(userShift), Coerce(numBlocks))),
        book( Book::Instance() )
        {

            //------------------------------------------------------------------
            //
            //
            // sanity check
            //
            //
            //------------------------------------------------------------------
            Y_STATIC_CHECK(Book::MinPageBytes>=sizeof(Chunk), BadMinPageShift);
            assert(userShift>=Book::MinPageShift);
            assert(userShift<=Book::MaxPageShift);

            std::cerr << "for userBlockSize     = " << userBlockSize << std::endl;
            std::cerr << "will allocate |chunk| = " << userBytes << " bytes" << std::endl;
            std::cerr << "numBlocks/chunk       = " << int(numBlocks) << std::endl;

            //------------------------------------------------------------------
            //
            //
            // first allocation : for workspace or chunks
            //
            //
            //------------------------------------------------------------------
            memBytes  = NextPowerOfTwo(Clamp(Book::MinPageBytes,userPageBytes,Book::MaxPageBytes),memShift);
            workspace = static_cast<Chunk *>(book.query(memShift));
            capacity  = memBytes / sizeof(Chunk);
            endChunk  = workspace+capacity;


            std::cerr << "memBytes=" << memBytes << "=2^" << memShift << " => capacity=" << capacity << " chunks per arena" << std::endl;

            //------------------------------------------------------------------
            //
            //
            // second allocation: create first chunk
            //
            //
            //------------------------------------------------------------------
            try { (void) makeInPlaceChunk(workspace); }
            catch(...) {
                releaseWorkspace();
                throw;
            }

            //------------------------------------------------------------------
            //
            //
            // first update
            //
            //
            //------------------------------------------------------------------
            count      = 1;
            available  = numBlocks;
            acquiring  = releasing = workspace;

            assert( isValid() );
        }



    }

}

namespace Yttrium
{
    namespace Memory
    {
        Chunk * findReleasing(const void * const addr,
                              Chunk *            lower,
                              Chunk *            upper) noexcept
        {
            assert(0!=addr);
            assert(0!=lower);
            assert(0!=upper);
            --upper;
            assert(upper>=lower);

            if(lower->owns(addr)) return lower;
            assert( OwnedByNext == lower->whose(addr) );

            if(upper->owns(addr)) return upper;
            assert( OwnedByPrev == upper->whose(addr) );

            std::cerr << "Need to implement further" << std::endl;

            exit(1);
        }

        void Arena:: release(void * const addr) noexcept
        {
            assert(0!=addr);
            assert(isValid());
            switch( releasing->whose(addr) )
            {
                case OwnedByCurr: // cached
                    break;

                case OwnedByPrev:
                    releasing = findReleasing(addr,workspace,releasing);
                    break;

                case OwnedByNext:
                    releasing = findReleasing(addr,++releasing,workspace+count);
                    break;
            }

            assert(releasing->owns(addr));
            releasing->release(addr,blockSize);

        }
    }

}


#include "y/exception.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {

        void Arena:: newChunkRequired()
        {
            assert(isValid());

            if(count>=capacity)
            {
                if(memShift>=Limits::MaxBlockShift) throw Specific::Exception(CallSign,"workspace too big");

                // prepare next metrics
                const unsigned nextMemShift  = memShift+1;
                const size_t   nextMemBytes  = memBytes << 1;
                const size_t   nextCapacity  = capacity << 1; assert( nextCapacity == nextMemBytes / sizeof(Chunk) );
                Chunk * const  nextWorkspace = static_cast<Chunk *>(book.query(nextMemShift));

                // transfer
                Memory::Stealth::Copy(nextWorkspace,workspace,memBytes);
                acquiring = nextWorkspace + (acquiring-workspace);
                releasing = nextWorkspace + (releasing-workspace);
                book.store(memShift,workspace);
                workspace = nextWorkspace;
                memShift  = nextMemShift;
                memBytes  = nextMemBytes;
                capacity  = nextCapacity;
                endChunk  = workspace + capacity;
                assert(isValid());
                std::cerr << "capacity is now " << capacity << std::endl;
                assert(count<capacity);
            }

            assert(count<capacity);


            //------------------------------------------------------------------
            //
            // append a new chunk
            //
            //------------------------------------------------------------------
            acquiring = makeInPlaceChunk(workspace+count);
            //std::cerr << "acquiring.data@" << (void*)(acquiring->data) << std::endl;
            ++count;
            available += numBlocks;
            assert(releasing<acquiring);

            //------------------------------------------------------------------
            //
            // update increasing memory
            //
            //------------------------------------------------------------------
            while(acquiring>workspace && acquiring[0].data < acquiring[-1].data)
            {
                //std::cerr << "swap memory" << std::endl;
                Memory::Stealth::Swap(acquiring, acquiring-1, sizeof(Chunk) );
                --acquiring;
            }
            assert(isValid());
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

