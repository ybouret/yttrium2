
#include "y/memory/operative.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    namespace Memory
    {

        Operative:: Operative(void * const entry,
                              const size_t count,
                              const size_t width,
                              QuitProc     _quit) :
        workspace( static_cast<uint8_t *>(entry) ),
        numBlocks( count ),
        blockSize( width ),
        quit( _quit )
        {
            assert(Good(workspace,numBlocks));
            assert(blockSize>0);
            assert(0!=quit);
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
                quit(ptr);
            }

        }

    }

}
