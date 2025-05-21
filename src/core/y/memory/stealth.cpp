
#include "y/memory/stealth.hpp"
#include "y/check/usual.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        void *       Stealth:: Address(void *const address)       noexcept { return address; }
        const void * Stealth:: Address(const void *const address) noexcept { return address; }

        void * Stealth:: Zero(void * const blockAddr, const size_t blockSize) noexcept
        {
            assert( Good(blockAddr,blockSize) );
            return memset(blockAddr,0,blockSize);
        }


        bool Stealth:: Are0(const void * const blockAddr,
                            const size_t       blockSize) noexcept
        {
            assert( Good(blockAddr,blockSize) );
            const uint8_t *p = static_cast<const uint8_t *>(blockAddr);
            for(size_t i=blockSize;i>0;--i)
                if(0 != *(p++)) return false;

            return true;
        }

    }

}
