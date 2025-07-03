
#include "y/random/fill.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    namespace Random
    {
        void Fill:: Block(Bits &        ran,
                          void * const  entry,
                          const size_t  count,
                          const uint8_t lower,
                          const uint8_t upper) noexcept
        {
            assert(Good(entry,count));
            assert(lower<=upper);
            uint8_t *p = static_cast<uint8_t *>(entry);
            for(size_t i=0;i<count;++i)
                *(p++) = ran.in<uint8_t>(lower,upper);
        }
    }

}
