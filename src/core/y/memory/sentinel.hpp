
#ifndef Y_Memory_Sentinel_Included
#define Y_Memory_Sentinel_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Sentinel
        {
        public:
            Sentinel(const void * const userBlock,
                     const size_t       userBytes) noexcept;
            ~Sentinel() noexcept;

            template <typename T> inline
            Sentinel(const T &pod) noexcept :
            addr( &pod ),
            size( sizeof(T) ),
            crc( Setup(addr,size) )
            {
            }
            
        private:
            Y_Disable_Copy_And_Assign(Sentinel);
            static uint32_t Setup(const void * const, const size_t ) noexcept;

            const void * const addr;
            const size_t       size;
            const uint32_t     crc;

        };
    }

}

#endif
