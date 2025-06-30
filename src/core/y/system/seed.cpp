
#include "y/system/seed.hpp"
#include "y/system/wall-time.hpp"
#include "y/system/pid.hpp"
#include "y/check/crc32.hpp"

#include <cassert>

namespace Yttrium
{
    namespace System
    {
        void Seed:: Fill(void * const entry,
                         const size_t count)
        {
            assert(entry);
            assert(count);
            const uint64_t  pid  = ProcessID::Get();
            const uint32_t  salt = CRC32::Run(pid,0);
            uint8_t * const byte = static_cast<uint8_t *>(entry);
            for(size_t i=0;i<count;++i)
            {
                const uint64_t temp = WallTime::Ticks();
                const uint32_t word = CRC32::Run(temp,salt);
                byte[i] = uint8_t(word);
            }
        }

    }

}
