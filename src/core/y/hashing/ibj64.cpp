
#include "y/hashing/ibj64.hpp"
#include "y/hashing/ibj32.hpp"

#include <cstdio>

namespace Yttrium
{
    namespace Hashing
    {
        
        const char * const IBJ64:: CallSign = "Hashing::IBJ64";

        IBJ64::  IBJ64() noexcept {}
        IBJ64:: ~IBJ64() noexcept {}

        const char * IBJ64:: callSign() const noexcept { return CallSign; }

        void    IBJ64::operator()(uint32_t &lword, uint32_t &rword) const noexcept
        {
            for(size_t iter=0;iter<4;++iter)
            {
                const uint32_t swp = rword;
                rword = IBJ32(rword) ^ lword;
                lword = swp;
            }
        }


    }
}

