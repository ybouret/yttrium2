
#include "y/random/fill.hpp"
#include "y/check/usual.hpp"
#include "y/memory/align.hpp"


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


        void Fill:: Block64(Bits &           ran,
                            uint64_t * const arr,
                            const size_t     bits) noexcept
        {
            assert( Good(arr,bits) );
            const size_t ceilBits = Alignment::On<64>::Ceil(bits);
            const size_t numWords = ceilBits / 64;
            if(numWords>0)
            {
                const size_t msi = numWords - 1;
                for(size_t i=0;i<msi;++i) arr[i] = ran.to<uint64_t>();
                if(bits>=ceilBits)
                {
                    //std::cerr << "bits=" << bits << " => ceil=" << ceilBits << " => #" << numWords << std::endl;
                    arr[msi] = ran.to<uint64_t>(64);
                }
                else
                {
                    const size_t rem = bits - (msi*64);
                    //std::cerr << "bits=" << bits << " => ceil=" << ceilBits << " => #" << msi << " +" << rem << std::endl;
                    arr[msi] = ran.to<uint64_t>(rem);
                }
            }
        }

    }

}
