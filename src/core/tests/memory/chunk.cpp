
#include "y/memory/chunk.hpp"
#include "y/memory/stealth.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/check/usual.hpp"

#include <cstring>

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


    {
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
                //std::cerr << "\tblockSize=" << blockSize << " / numBlocks=" << (int)chunk.userBlocks << std::endl;
                memset(addr,0,sizeof(addr));
                size = 0;
                fill(addr,size,chunk,blockSize,ran);
                for(size_t iter=0;iter<8;++iter)
                {
                    ran.shuffle(addr,size);
                    empty(size/2,addr,size,chunk,blockSize);
                    fill(addr,size,chunk,blockSize,ran);
                }
                Y_ASSERT(0==chunk.freeBlocks);
                empty(0,addr,size,chunk,blockSize);
            }
            free(blockAddr);
        }
    }




    for(size_t blockSize=1;blockSize<=64;++blockSize)
    {
        std::cerr << "blockSize=" << std::setw(3) << blockSize; //<< std::endl;
        unsigned     userShift = 0;
        const size_t userBytes = Memory::Chunk::UserBytesFor(blockSize,4096,userShift);
        Y_ASSERT(size_t(1)<<userShift == userBytes);
    }



    Y_SIZEOF(Memory::Chunk);

}
Y_UDONE()

