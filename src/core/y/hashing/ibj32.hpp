//! \file

#ifndef Y_Hashing_BJH32_Included
#define Y_Hashing_BJH32_Included 1

#include "y/calculus/alignment.hpp"

#include <iostream>
#include <cassert>

namespace Yttrium
{

    namespace Hashing
    {

        //! full 4-byte avalanche
        /**
         \param  a uint32_t input
         \return hashed value
         */
        inline uint32_t IBJ32(uint32_t a) noexcept
        {
            a = (a+0x7ed55d16) + (a<<12);
            a = (a^0xc761c23c) ^ (a>>19);
            a = (a+0x165667b1) + (a<<5);
            a = (a+0xd3a2646c) ^ (a<<9);
            a = (a+0xfd7046c5) + (a<<3);
            a = (a^0xb55a4f09) ^ (a>>16);
            return a;
        }

        
    }

}

#endif

