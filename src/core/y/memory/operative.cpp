
#include "y/memory/operative.hpp"
#include "y/check/usual.hpp"
#include "y/memory/stealth.hpp"

#include <iostream>
namespace Yttrium
{
    namespace Memory
    {

        Operative:: Operative(void * const       entry,
                              const size_t       count,
                              const size_t       width,
                              InitProc const     onInit,
                              void * const       source,
                              void * const       params,
                              QuitProc const     onQuit) :
        workspace( static_cast<uint8_t *>(entry) ),
        numBlocks( 0 ),
        blockSize( width ),
        quit( onQuit )
        {
            assert(Good(entry,count) );
            assert(blockSize>0);
            assert(0!=quit);
            assert(0!=onInit);

            std::cerr << "Building " << count << std::endl;
            try {
                uint8_t * ptr = workspace;
                while(numBlocks<count)
                {
                    const size_t indexx = numBlocks+1;
                    assert( Stealth::Are0(ptr,blockSize) );
                    onInit(ptr,source,indexx,params);
                    ptr      += blockSize;
                    numBlocks = indexx;
                }
            }
            catch(...)
            {
                release_();
            }
        }

        Operative:: ~Operative() noexcept
        {
            release_();
        }

        void Operative:: release_() noexcept
        {
            assert(Good(workspace,numBlocks));
            assert(blockSize>0);
            assert(0!=quit);

            uint8_t * ptr = workspace + (blockSize*numBlocks);
            while(numBlocks>0)
            {
                --numBlocks;
                ptr -= blockSize;
                try { quit(ptr); } catch(...) { }
            }

        }

    }

}
