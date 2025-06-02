
#ifndef Y_Memory_Sentinel_Included
#define Y_Memory_Sentinel_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //! memory sentinel
        class Sentinel
        {
        public:

            //! setup from memory \param userBlock address \param userBytes length
            Sentinel(const void * const userBlock,
                     const size_t       userBytes) noexcept;

            //! cleanup
            ~Sentinel() noexcept;

            //! setup from POD object \param pod binary object
            template <typename T> inline
            Sentinel(const T &pod) noexcept :
            addr( &pod ),
            size( sizeof(T) ),
            crc( Setup(addr,size) )
            {
            }
            
        private:
            Y_Disable_Copy_And_Assign(Sentinel); //!< discading

            //! compute crc of source area \return CRC32
            static uint32_t Setup(const void * const, const size_t ) noexcept;

            const void * const addr; //!< persisent user's memory
            const size_t       size; //!< persistent memory size
            const uint32_t     crc;  //!< original CRC

        };
    }

}

#endif
