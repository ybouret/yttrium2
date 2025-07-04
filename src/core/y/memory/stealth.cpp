
#include "y/memory/stealth.hpp"
#include "y/check/usual.hpp"
#include "y/core/utils.hpp"
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


        void    Stealth:: Swap(void * const lhsBlock,
                               void * const rhsBlock,
                               const size_t blockSize) noexcept
        {
            assert( Good(lhsBlock,blockSize) );
            assert( Good(rhsBlock,blockSize) );
            uint8_t * lhs = static_cast<uint8_t *>(lhsBlock);
            uint8_t * rhs = static_cast<uint8_t *>(rhsBlock);
            for(size_t i=blockSize;i>0;--i)
                Yttrium::Swap( *(lhs++), *(rhs++) );
        }


        void * Stealth:: Copy(void * const       target,
                              const void * const source,
                              const size_t       bytes) noexcept
        {
            assert( Good(target,bytes) );
            assert( Good(source,bytes) );
            return memcpy(target,source,bytes);
        }

        void * Stealth:: SafeCopy(void * const target,
                                  void * const source,
                                  const size_t bytes) noexcept
        {
            assert( Good(target,bytes) );
            assert( Good(source,bytes) );
            uint8_t * lhs = static_cast<uint8_t *>(target);
            uint8_t * rhs = static_cast<uint8_t *>(source);
            for(size_t i=bytes;i>0;--i)
            {
                *(lhs++) = *rhs;
                *(rhs++) = 0;
            }
            return target;
        }


        void * Stealth:: Move(void * const       target,
                              const void * const source,
                              const size_t       bytes) noexcept
        {
            assert( Good(target,bytes) );
            assert( Good(source,bytes) );
            return memmove(target,source,bytes);
        }

        void * Stealth:: Incr(void * const addr,
                              const size_t delta) noexcept
        {
            return static_cast<char *>(addr)+delta;
        }


        void * Stealth:: Decr(void * const addr,
                              const size_t delta) noexcept
        {
            return static_cast<char *>(addr)-delta;
        }


        ptrdiff_t Stealth:: Diff(const void * const ini, const void *const end) noexcept
        {
            return static_cast<const char *>(end) - static_cast<const char *>(ini);
        }


    }

}
