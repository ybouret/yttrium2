
//! \file

#ifndef Y_Random_Fill_Included
#define Y_Random_Fill_Included 1

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Random
    {

        struct Fill
        {

            static void Block(Bits &,
                              void * const,
                              const size_t,
                              const uint8_t= 0x00,
                              const uint8_t= 0xff) noexcept;


            template <typename T>
            static inline
            void Variable(Bits &ran, T &arg,
                          const uint8_t lower = 0x00,
                          const uint8_t upper = 0xff ) noexcept
            {
                Block(ran,&arg,sizeof(T),lower,upper);
            }
        };

    }

}

#endif

