
#include "y/calculus/bits-for.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Calculus
    {
        const unsigned BitsFor::Table[256] =
        {
            0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
        };

        unsigned BitsFor::Count(const uint8_t &u) noexcept
        {
            return Table[u];
        }

        unsigned BitsFor:: Count(const uint16_t &w) noexcept
        {
            if(w>0xff) return 8+BitsFor::Table[ (w>>8) ];

            assert(w<=0xff);
            return BitsFor::Table[w];
        }


        unsigned BitsFor:: Count(const uint32_t &w) noexcept
        {
            if(w>0x00ffffff) return 24+BitsFor::Table[ (w>>24) ];
            if(w>0x0000ffff) return 16+BitsFor::Table[ (w>>16) ];
            if(w>0x000000ff) return 8 +BitsFor::Table[ (w>>8) ];
            assert(w<=0xff);
            return BitsFor::Table[w];
        }



        unsigned BitsFor:: Count(const uint64_t &w) noexcept
        {
            if(w>0x00ffffffffffffffULL) return 56+BitsFor::Table[ (w>>56) ];
            if(w>0x0000ffffffffffffULL) return 48+BitsFor::Table[ (w>>48) ];
            if(w>0x000000ffffffffffULL) return 40+BitsFor::Table[ (w>>40) ];
            if(w>0x00000000ffffffffULL) return 32+BitsFor::Table[ (w>>32) ];
            if(w>0x0000000000ffffffULL) return 24+BitsFor::Table[ (w>>24) ];
            if(w>0x000000000000ffffULL) return 16+BitsFor::Table[ (w>>16) ];
            if(w>0x00000000000000ffULL) return 8 +BitsFor::Table[ (w>>8) ];
            assert(w<=0xffULL);
            return BitsFor::Table[w];
        }

    }

}


