
//! \file

#ifndef Y_Random_Fill_Included
#define Y_Random_Fill_Included 1

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Random
    {

        //! fill memory with random bits
        struct Fill
        {

            //! generic fill each byte with given range
            static void Block(Bits &,
                              void * const,
                              const size_t,
                              const uint8_t= 0x00,
                              const uint8_t= 0xff) noexcept;

            static void Block64(Bits &ran,
                                uint64_t * const arr,
                                const size_t     bits) noexcept;
            

            //! fill object with random bits
            /**
             \param ran   Bits
             \param arg   the object
             \param lower lower byte value
             \param upper upper byte value
             */
            template <typename T>
            static inline
            void Variable(Bits &        ran,
                          T &           arg,
                          const uint8_t lower = 0x00,
                          const uint8_t upper = 0xff ) noexcept
            {
                Block(ran,&arg,sizeof(T),lower,upper);
            }
        };

    }

}

#endif

