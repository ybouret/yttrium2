//! \file

#ifndef Y_CRC32_Included
#define Y_CRC32_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! basic CRC32 algorithm
    //
    //
    //__________________________________________________________________________
    struct CRC32
    {
        static const uint32_t Table[256];
        
        //______________________________________________________________________
        //
        //! update crc
        /**
         \param crc current crc
         \param blockAddr block address
         \param blockSize block size
         \return new crc
         */
        //______________________________________________________________________
        static uint32_t Run(uint32_t           crc,
                            const void * const blockAddr,
                            size_t             blockSize) noexcept;


        //______________________________________________________________________
        //
        //! crc of a block
        /**
         \param blockAddr block address
         \param blockSize block size
         \return computed crc
         */
        //______________________________________________________________________
        static uint32_t Of(const void * const blockAddr,
                           const size_t       blockSize) noexcept;

        template <typename T> static inline
        uint32_t Run(const T &arg, uint32_t crc = 0x00) noexcept
        {
            const uint8_t *p = (const uint8_t *) & arg;

            crc = ~crc;
            for(size_t i=sizeof(T);i>0;--i)
                crc = (crc >> 8) ^ Table[(crc & 0xff) ^ *(p++)];
            return ~crc;
        }

    };

}

#endif
