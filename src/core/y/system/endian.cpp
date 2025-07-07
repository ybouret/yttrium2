
#include "y/system/endian.hpp"

namespace Yttrium
{

    bool Endian:: Little() noexcept
    {
        static const uint8_t  byte[2]={0,1};
        const uint16_t        word = *(const uint16_t*)(&(byte[0]));
        return 0x0100 == word;
    }

    bool Endian:: Big()    noexcept
    {
        return !Little();
    }

    const char * Endian:: HumanReadable()  noexcept
    {
        if( Little() ) return "LittleEndian"; else return "BigEndian";
    }
}
