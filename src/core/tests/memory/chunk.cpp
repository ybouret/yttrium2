
#include "y/memory/system.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

#include "y/check/usual.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Chunk
        {
        public:
            static uint8_t NumBlocksFor(const size_t userBytes,
                                        const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                const size_t res = userBytes/blockSize;
                if(res<=0xff) return static_cast<uint8_t>(res); else return 0xff;
            }


            //! initialize provided memory
            /**
             \param blockAddr available memory >= numBlocks*blockSize
             \param numBlocks in 0:255
             */
            explicit Chunk(void * const  blockAddr,
                           const uint8_t numBlocks,
                           const size_t  blockSize) noexcept :
            data( static_cast<uint8_t *>(blockAddr) ),
            firstBlock(0),
            freeBlocks(numBlocks),
            userBlocks(numBlocks),
            last( data + (blockSize * static_cast<size_t>(numBlocks)) )
            {
                assert(Good(blockAddr,numBlocks));
                uint8_t *p=data;
                for(uint8_t i=0;i!=numBlocks;p += blockSize)
                {
                    *p = ++i;
                }
            }

            inline ~Chunk() noexcept
            {
                assert(freeBlocks<=userBlocks);
                if(freeBlocks<userBlocks)
                {
                    std::cerr << "missing" << std::endl;
                }
            }

            void * acquire(const size_t blockSize) noexcept
            {
                if(freeBlocks<=0) return 0;
                uint8_t * const p = &data[ firstBlock * blockSize ];
                firstBlock = *p;
                --freeBlocks;
                return memset(p,0,blockSize);
            }

            void release(void * const p, const size_t blockSize) noexcept
            {
                assert(0!=p);
                assert(freeBlocks<userBlocks);
                uint8_t * const toRelease = static_cast<uint8_t *>(p);
                const size_t    theOffset = toRelease-data;
                assert( toRelease >= data );
                assert( toRelease <  last );
                assert( 0 == theOffset % blockSize );
                *toRelease = firstBlock;
                const size_t deltaBlocks = theOffset/blockSize; assert(deltaBlocks<=0xff);
                firstBlock = static_cast<uint8_t>(deltaBlocks);
                ++freeBlocks;
            }


            uint8_t * const       data;
            uint8_t               firstBlock;
            uint8_t               freeBlocks;
            const uint8_t         userBlocks;
            const uint8_t * const last;

        private:
            Y_Disable_Copy_And_Assign(Chunk);
        };


    }
}

using namespace Yttrium;

namespace
{
    static inline
    void fill( void * addr[], size_t &size , Memory::Chunk &chunk, const size_t blockSize, System::Rand &ran) noexcept
    {
        while(true)
        {
            void * const p = chunk.acquire(blockSize);
            if(!p) break;
            ran.fill(addr[size++] = p,blockSize);
        }
    }

    static inline
    void empty( const size_t target, void * addr[], size_t &size, Memory::Chunk &chunk, const size_t blockSize)
    {
        while(size>target)
        {
            chunk.release(addr[--size], blockSize);
        }
    }

}

Y_UTEST(memory_chunk)
{
    System::Rand    ran;
    //Memory::System &allocator = Memory::System::Instance();

    Y_SIZEOF(Memory::Chunk);


    void * addr[256];
    size_t size = 0;

    for(size_t userBytes=1; userBytes <= 1024; userBytes <<= 1)
    {
        std::cerr << "userBytes=" << userBytes << std::endl;
        void * const blockAddr = calloc(1,userBytes);
        if(0==blockAddr) throw Exception("no memory");
        for(size_t blockSize=1;blockSize<=256;++blockSize)
        {
            Memory::Chunk chunk(blockAddr, Memory::Chunk::NumBlocksFor(userBytes,blockSize), blockSize);
            std::cerr << "\tblockSize=" << blockSize << " / numBlocks=" << (int)chunk.userBlocks << std::endl;
            memset(addr,0,sizeof(addr));
            size = 0;
            fill(addr,size,chunk,blockSize,ran);
            for(size_t iter=0;iter<8;++iter)
            {
                ran.shuffle(addr,size);
                empty(size/2,addr,size,chunk,blockSize);
                fill(addr,size,chunk,blockSize,ran);
            }
            empty(0,addr,size,chunk,blockSize);
        }
        free(blockAddr);
    }



}
Y_UDONE()

