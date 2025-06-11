
#include "y/memory/small/arena.hpp"
#include "y/memory/small/chunk.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/memory/small/ledger.hpp"
#include "y/core/utils.hpp"
#include "y/check/static.hpp"
#include "y/check/crc32.hpp"

#include <iostream>
#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {


            size_t Arena:: Hash(const size_t bs) noexcept
            {
                const uint16_t w = uint16_t(bs);
                return CRC32::Run(w);;
            }

            const char * const Arena:: CallSign = "Memory::Small::Arena";
            static const char  ErrorHeader[]    = "*** [FAILED] ";

#define Y_Arena_Check(EXPR) do { if ( !(EXPR) ) { std::cerr << ErrorHeader << #EXPR << std::endl;  return false; } } while(false)

            bool Arena:: isValid() const noexcept
            {
                Y_Arena_Check(0!=workspace);
                Y_Arena_Check(occupied<=capacity);
                Y_Arena_Check(0!=acquiring);
                Y_Arena_Check(acquiring>=workspace);
                Y_Arena_Check(acquiring<workspace+occupied);
                Y_Arena_Check(0!=releasing);
                Y_Arena_Check(releasing>=workspace);
                Y_Arena_Check(releasing<workspace+occupied);
                Y_Arena_Check(!(available<=0 && freeChunk));

                if(freeChunk)
                {
                    Y_Arena_Check(freeChunk>=workspace);
                    Y_Arena_Check(freeChunk<workspace+occupied);
                    Y_Arena_Check(freeChunk->isFree());
                }

                for(size_t i=0,j=1;j<occupied;++i,++j)
                {
                    const Chunk & lhs = workspace[i];
                    const Chunk & rhs = workspace[j];
                    Y_Arena_Check(lhs.data<rhs.data);
                }

                return true;
            }


            void Arena:: releaseWorkspace() noexcept
            {
                assert(0==occupied);
                assert(0!=workspace);
                assert(capacity>0);
                assert(memBytes>0);
                assert(memShift>0);
                assert(0==acquiring);
                assert(0==releasing);
                assert( Ledger::Exists() );
                static Ledger & ledger = Ledger::Location();

                ledger.store(memShift,workspace);
                memBytes  = 0;
                memShift  = 0;
                capacity  = 0;
                workspace = 0;
            }


            void Arena:: releaseAllChunks() noexcept
            {
                assert( isValid() );
                assert(Ledger::Exists());
                static Ledger & ledger = Ledger::Location();

                acquiring = releasing = 0;
                size_t missing = 0;
                while(occupied>0)
                {
                    Chunk &current = workspace[--occupied];
                    missing += current.userBlocks-current.freeBlocks;
                    ledger.store(userShift,current.data);
                    Memory::Stealth::Zero( &current, sizeof(Chunk) );
                }
                if(missing>0)
                {
                    std::cerr << "*** " << CallSign << "[" << std::setw(3) << blockSize << "] missing #" << missing << std::endl;
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
                static Ledger & ledger = Ledger::Instance();
                return new (addr) Chunk(ledger.query(userShift),numBlocks,blockSize);
            }



            Arena:: Arena(const size_t userBlockSize,
                          const size_t userPageBytes) :
            available(0),
            acquiring(0),
            releasing(0),
            freeChunk(0),
            workspace(0),
            occupied(0),
            capacity(0),
            memBytes(0),
            memShift(0),
            blockSize(userBlockSize),
            userShift(0),
            numBlocks(0),
            userBytes( Chunk::UserBytesFor(blockSize, userPageBytes, Coerce(userShift), Coerce(numBlocks))),
            hkey( Hash(blockSize) ),
            next(0),
            prev(0)
            {

                //--------------------------------------------------------------
                //
                //
                // sanity check
                //
                //
                //--------------------------------------------------------------
                Y_STATIC_CHECK(Ledger::MinPageBytes>=sizeof(Chunk), BadMinPageShift);
                assert(userShift>=Ledger::MinPageShift);
                assert(userShift<=Ledger::MaxPageShift);
                Ledger & ledger = Ledger::Instance();

                //--------------------------------------------------------------
                //
                //
                // first allocation : for workspace or chunks
                //
                //
                //--------------------------------------------------------------
                memBytes  = NextPowerOfTwo(Clamp(Ledger::MinPageBytes,userPageBytes,Ledger::MaxPageBytes),memShift);
                workspace = static_cast<Chunk *>(ledger.query(memShift));
                capacity  = memBytes / sizeof(Chunk);



                //--------------------------------------------------------------
                //
                //
                // second allocation: create first chunk
                //
                //
                //--------------------------------------------------------------
                try { (void) makeInPlaceChunk(workspace); }
                catch(...) {
                    releaseWorkspace();
                    throw;
                }

                //--------------------------------------------------------------
                //
                //
                // first update
                //
                //
                //--------------------------------------------------------------
                occupied   = 1;
                available  = numBlocks;
                acquiring  = releasing = workspace;
                assert( isValid() );
            }


        }

    }

}

#include "y/system/error.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            //------------------------------------------------------------------
            //
            //
            //
            // releasing
            //
            //
            //
            //------------------------------------------------------------------

            namespace
            {
#define Y_Memory_Arena_Release_Critical() do {\
/**/    if(upper<lower) Libc::Error::Critical(EINVAL, fmt, Arena::CallSign, addr); \
} while(false)

                static inline
                Chunk * findReleasing(const void * const addr,
                                      Chunk *            lower,
                                      Chunk *            upper) noexcept
                {
                    static const char fmt[] = "%s: no owner of @%p";
                    assert(0!=addr);
                    assert(0!=lower);
                    assert(0!=upper);
                    --upper;
                    Y_Memory_Arena_Release_Critical();

                    if(lower->owns(addr)) return lower;
                    assert( OwnedByNext == lower->whose(addr) );

                    if(upper->owns(addr)) return upper;
                    assert( OwnedByPrev == upper->whose(addr) );


                PROBE:
                    Chunk * const probe = lower + ( (upper-lower)>>1 );
                    switch( probe->whose(addr) )
                    {
                        case OwnedByCurr:
                            break;

                        case OwnedByNext:
                            (lower=probe)++;
                            Y_Memory_Arena_Release_Critical();
                            goto PROBE;

                        case OwnedByPrev:
                            (upper=probe)--;
                            Y_Memory_Arena_Release_Critical();
                            goto PROBE;
                    }
                    return probe;
                }
            }


            void Arena:: release(void * const addr) noexcept
            {
                assert(0!=addr);
                assert(isValid());
                assert( Ledger::Exists() );
                static Ledger & ledger = Ledger::Location();

                //--------------------------------------------------------------
                //
                // look for releasing
                //
                //--------------------------------------------------------------
                switch( releasing->whose(addr) )
                {
                    case OwnedByCurr: // cached
                        break;

                    case OwnedByPrev:
                        releasing = findReleasing(addr,workspace,releasing);
                        break;

                    case OwnedByNext:
                        releasing = findReleasing(addr,++releasing,workspace+occupied);
                        break;
                }

                //--------------------------------------------------------------
                //
                // return block to its chunk
                //
                //--------------------------------------------------------------
                assert(releasing->owns(addr));
                ++available;
                if( releasing->release(addr,blockSize) )
                {
                    assert( releasing->isFree() );
                    if(0==freeChunk)
                    {
                        freeChunk = releasing;
                    }
                    else
                    {
                        //------------------------------------------------------
                        // get rid of highest memory free chunk and keep releasing
                        //------------------------------------------------------
                        {
                            if(freeChunk<releasing)
                                Swap(freeChunk,releasing);
                            assert(releasing<freeChunk);
                            assert(releasing->data<freeChunk->data);
                            assert(available>=numBlocks);

                            // return blocks
                            ledger.store(userShift,freeChunk->data);
                            available -= numBlocks;

                            // update workspace
                            Stealth::Move(freeChunk,freeChunk+1,sizeof(Chunk)*(--occupied - static_cast<size_t>(freeChunk-workspace)) );
                            Stealth::Zero(workspace+occupied,sizeof(Chunk));
                            freeChunk = 0;
#if !defined(NDEBUG)
                            size_t ready = 0;
                            for(size_t i=0;i<occupied;++i) ready += workspace[i].freeBlocks;
                            assert(ready==available);
#endif
                        }

                        //------------------------------------------------------
                        // update acquiring status
                        //------------------------------------------------------
                        if(acquiring>releasing)
                            --acquiring;

                        assert(isValid());
                    }
                }
            }


        }
    }
}


#include "y/exception.hpp"
#include "y/decimal.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            namespace
            {
                static inline
                Chunk * findAcquiring(const Chunk * const base,
                                      const Chunk * const last,
                                      Chunk * const       acquiring) noexcept
                {
                    static const char fmt[] = "%s: no chunk with free block";

                    assert(acquiring>=base);
                    assert(acquiring<last);
                    assert(0==acquiring->freeBlocks);
                    Chunk * lower = acquiring;
                    Chunk * upper = acquiring;

                INTERLEAVED:
                    if(--lower<base)
                        goto UPPER_ONLY;

                    if(lower->freeBlocks>0)
                        return lower;

                    if(++upper>=last)
                        goto LOWER_ONLY;

                    if(upper->freeBlocks>0)
                        return upper;

                    goto INTERLEAVED;

                LOWER_ONLY:
                    assert(upper>=last);

                    if(--lower<base)
                        Libc::Error::Critical(EINVAL,fmt,Arena::CallSign);

                    if(lower->freeBlocks>0)
                        return lower;

                    goto LOWER_ONLY;

                UPPER_ONLY:
                    assert(lower<base);

                    if(++upper>=last)
                        Libc::Error::Critical(EINVAL,fmt,Arena::CallSign);

                    if(upper->freeBlocks>0)
                        return upper;

                    goto UPPER_ONLY;

                }
            }

            void Arena:: newChunkRequired()
            {
                assert(isValid());
               // Y_Arena_Print("newChunkRequired");
                if(occupied>=capacity)
                {
                    assert(0==freeChunk);
                    if(memShift>=Limits::MaxBlockShift) throw Specific::Exception(CallSign,"workspace too big");
                    Ledger & ledger = Ledger::Instance();

                    //--------------------------------------------------------------
                    // prepare next metrics
                    //--------------------------------------------------------------
                    const unsigned nextMemShift  = memShift+1;
                    const size_t   nextMemBytes  = memBytes << 1;
                    const size_t   nextCapacity  = capacity << 1; assert( nextCapacity == nextMemBytes / sizeof(Chunk) );
                    Chunk * const  nextWorkspace = static_cast<Chunk *>(ledger.query(nextMemShift));

                    //--------------------------------------------------------------
                    // transfer
                    //--------------------------------------------------------------
                    Memory::Stealth::Copy(nextWorkspace,workspace,memBytes);
                    acquiring = nextWorkspace + (acquiring-workspace);
                    releasing = nextWorkspace + (releasing-workspace);
                    ledger.store(memShift,workspace);
                    workspace = nextWorkspace;
                    memShift  = nextMemShift;
                    memBytes  = nextMemBytes;
                    capacity  = nextCapacity;
                    assert(isValid());
                    assert(occupied<capacity);
                }

                assert(occupied<capacity);


                //------------------------------------------------------------------
                //
                // append a new chunk
                //
                //------------------------------------------------------------------
                acquiring = makeInPlaceChunk(workspace+occupied);
                ++occupied;
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
                assert(isValid());
                if(available<=0)
                {
                    newChunkRequired();
                    assert(available>0);
                }
                assert(available>0);


                if( acquiring->freeBlocks <= 0 )
                    acquiring = findAcquiring(workspace,workspace+occupied,acquiring);

                assert(0!=acquiring);
                assert(acquiring->freeBlocks>0);

                --available;
                if( freeChunk == acquiring) freeChunk = 0;
                return acquiring->acquire(blockSize);
            }

        }

    }
}

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {
            bool Arena:: owns(const void * const addr) const noexcept
            {
                assert(0!=addr);
                const Chunk * ch = workspace;
                for(size_t i=occupied;i>0;--i,++ch)
                {
                    if(ch->owns(addr)) return true;
                }
                return false;
            }

        }
    }
}

#include "y/xml/element.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {
            void Arena:: display(std::ostream &os, size_t indent) const
            {
                XML::Indent(os,indent) << "bs=" << std::setw(4) << blockSize;
                std::cerr << " #free";
                for(size_t i=0;i<occupied;++i)
                {
                    const Chunk &ch = workspace[i];
                    os << " " << std::setw(3) << int(ch.freeBlocks) << "/" << std::setw(3) << int(ch.userBlocks);
                }
                os << std::endl;
            }

        }

    }

}

