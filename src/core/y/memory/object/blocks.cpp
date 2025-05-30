#include "y/memory/object/blocks.hpp"
#include "y/memory/object/book.hpp"
#include "y/memory/object/arena.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/core/utils.hpp"
#include "y/type/destruct.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/align.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {


            Blocks:: Blocks(const size_t userPageBytes) :
            pageShift(0),
            pageBytes( NextPowerOfTwo( Clamp(Book::MinPageBytes,userPageBytes,Book::MaxPageBytes), Coerce(pageShift)))
            {
                
            }

            Blocks:: ~Blocks() noexcept
            {
                
            }
#if 0

            namespace
            {


                class MetaArena
                {
                public:
                    typedef Core::PoolOf<MetaArena> Pool;
                    inline MetaArena(const size_t blockSize,
                                     const size_t pageBytes) :
                    arena(blockSize,pageBytes),
                    next(0)
                    {
                    }


                    inline ~MetaArena() noexcept
                    {
                    }


                    Arena      arena;
                    MetaArena *next;
                private:
                    Y_Disable_Copy_And_Assign(MetaArena);
                };


                typedef RawListOf<Arena> ArenaList;
                static const size_t      MinArenaList = 32;

            }

            class Blocks :: Code
            {
            public:
                typedef RawListOf<Arena> ArenaList;


                explicit Code(const size_t userPageBytes,
                              const size_t userCodeBytes) :
                acquiring(0),
                releasing(0),
                authority( sizeof(MetaArena), userPageBytes ),
                pageBytes(userPageBytes),
                arenaPool(),
                hashTable(0),
                tableSize(0),
                tableMask(0)
                {
                    static const size_t Header = sizeof(Code);
                    static const size_t Origin = Memory::Align::Compute::CeilOf<Header>::Value;
                    std::cerr << Origin << std::endl;
                    const size_t availableBytes = userCodeBytes-Origin;
                    std::cerr << "avail=" << availableBytes << std::endl;
                    const size_t maxTableSize = availableBytes / sizeof(ArenaList);
                    if(maxTableSize<=0) throw Specific::Exception("Memory::Object::Blocks","no memory for hashTable");
                    Coerce(tableSize) = PrevPowerOfTwo(maxTableSize); std::cerr << "tableSize=" << tableSize << std::endl;
                    Coerce(tableMask) = tableSize-1;
                    Coerce(hashTable) = static_cast<ArenaList *>(Stealth::Incr(this,Origin));
                    for(size_t i=0;i<tableSize;++i)
                        new( hashTable+i ) ArenaList();

                }

                ~Code() noexcept
                {
                    // clean table
                    for(size_t i=tableSize;i>0;)
                        Destruct( &hashTable[--i] );
                    while(arenaPool.size>0)
                    {
                        MetaArena * const ma = arenaPool.query();
                        authority.release( Destructed(ma) );
                    }
                }

                inline Arena * search(const size_t blockSize) noexcept
                {
                    ArenaList &list = hashTable[ Arena::Hash(blockSize) & tableMask ];
                    for(Arena *a=list.head;a;a=a->next)
                    {
                        if(blockSize==a->blockSize) return list.moveToFront(a);
                    }
                    return 0;
                }

                void * acquire(const size_t blockSize)
                {
                    if(0!=acquiring && blockSize==acquiring->blockSize)
                    {
                        // cached!
                        return acquiring->acquire();
                    }
                    else
                    {
                        Arena * const a = search(blockSize);
                        return (acquiring = (0!=a) ? a : create(blockSize))->acquire();
                    }
                }

                void release(void * const blockAddr,
                             const size_t blockSize) noexcept
                {
                    if(0!=releasing && blockSize==releasing->blockSize)
                    {
                        // cached
                        releasing->release(blockAddr);
                    }
                    else
                    {
                        Arena * const a = search(blockSize);
                        if(!a) Libc::Error::Critical(EINVAL, "invalid object block address");
                        (releasing=a)->release(blockAddr);
                    }
                }


                Arena *                acquiring;
                Arena *                releasing;
                Arena                  authority;
                const size_t           pageBytes;
                MetaArena::Pool        arenaPool;
                ArenaList *            hashTable;
                const size_t           tableSize;
                const size_t           tableMask;

                Arena * create(const size_t blockSize)
                {
                    void * const addr = authority.acquire();
                    try {
                        MetaArena * const ma = arenaPool.store( new(addr) MetaArena(blockSize,pageBytes) );
                        return hashTable[ ma->arena.hkey & tableMask ].pushHead( &(ma->arena) );
                    }
                    catch(...)
                    {
                        authority.release(addr);
                        throw;
                    }
                }


            private:
                Y_Disable_Copy_And_Assign(Code);
            };

            Blocks:: Blocks(const size_t userPageSize) :
            book( Book::Instance() ),
            pageShift(0),
            pageBytes( NextPowerOfTwo( Clamp(Book::MinPageBytes,userPageSize,Book::MaxPageBytes), Coerce(pageShift))),
            codeShift(0),
            codeBytes( NextPowerOfTwo( Clamp(Book::MinPageBytes,sizeof(Code) + MinArenaList * sizeof(ArenaList),Book::MaxPageBytes), Coerce(codeShift)) ),
            code( static_cast<Code *>( book.query(codeShift)) )
            {
                std::cerr << "sizeof(Code)      = " << sizeof(Code)      << std::endl;
                std::cerr << "sizeof(Arena)     = " << sizeof(Arena)     << std::endl;
                std::cerr << "sizeof(MetaArena) = " << sizeof(MetaArena)     << std::endl;
                std::cerr << "CodeBytes         = " << codeBytes << std::endl;

                try {
                    new (code) Code(pageBytes,codeBytes);
                }
                catch(...)
                {
                    book.store(codeShift,code);
                    throw;
                }
            }



            Blocks:: ~Blocks() noexcept
            {
                assert(0!=code);
                book.store(codeShift, Destructed(code) );
                code=0;
            }

            void * Blocks:: acquire(const size_t blockSize)
            {
                assert(0!=code);
                assert(blockSize>0);
                return code->acquire(blockSize);
            }

            void Blocks:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(0!=code);
                assert(0!=blockAddr);
                assert(blockSize>0);
                code->release(blockAddr,blockSize);
            }
#endif

        }
    }
}

