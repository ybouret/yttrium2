
#include "y/memory/object/chunk.hpp"
#include "y/memory/stealth.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/check/usual.hpp"
#include "y/calculus/base2.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{
    static inline
    void fill( void * addr[], size_t &size , Memory::Object::Chunk &chunk, const size_t blockSize, System::Rand &ran) noexcept
    {
        while(true)
        {
            void * const p = chunk.acquire(blockSize);
            if(!p) break;
            ran.fill(addr[size++] = p,blockSize);
        }
    }

    static inline
    void empty( const size_t target, void * addr[], size_t &size, Memory::Object::Chunk &chunk, const size_t blockSize)
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
                Memory::Object::Chunk chunk(blockAddr, Memory::Object::Chunk::NumBlocksFor(blockSize,userBytes), blockSize);
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




    for(size_t blockSize=1;blockSize<=512;++blockSize)
    {
        std::cerr << "blockSize=" << std::setw(3) << blockSize; //<< std::endl;
        unsigned     userShift = 0;
        uint8_t      numBlocks = 0;
        const size_t userBytes = Memory::Object::Chunk::UserBytesFor(blockSize,4096,userShift,numBlocks);
        Y_ASSERT(size_t(1)<<userShift == userBytes);
        Y_ASSERT(Memory::Object::Chunk::NumBlocksFor(blockSize,userBytes) == numBlocks);
        std::cerr << " | numBlocks = " << std::setw(3) << int(numBlocks);
        std::cerr << " | userBytes = " << std::setw(8) << userBytes;
        std::cerr << std::endl;
    }



    Y_SIZEOF(Memory::Object::Chunk);
    Y_CHECK(IsPowerOfTwo( sizeof(Memory::Object::Chunk)) );
}
Y_UDONE()

