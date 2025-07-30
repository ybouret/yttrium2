
#include "y/calculus/bytes-for.hpp"
#include "y/calculus/alignment.hpp"
#include "y/utest/run.hpp"

#include "y/format/hexadecimal.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static
    inline void checkBytes( Random::Bits & ran)
    {
        const size_t MaxBits = 8 * sizeof(T);
        std::cerr << "check " << MaxBits << "-bits" << std::endl;
        for(size_t i=0;i<=MaxBits;++i)
        {
            const size_t n    = Alignment::On<8>::Ceil(i) / 8;
            for(size_t iter=0;iter<10;++iter)
            {
                const T      word = ran.to<T>(i);
                Y_ASSERT( BytesFor(word) == n );
            }

        }
    }
}

Y_UTEST(calculus_bytes_for)
{
    Random::MT19937 ran;

    {
        {
            const uint8_t zero = 0; Y_CHECK(Calculus::BytesFor::Count(zero)==0);
            for(unsigned i=1;i<256;++i)
            {
                const uint8_t b = uint8_t(i);
                Y_ASSERT(1==Calculus::BytesFor::Count(b));
            }
        }
    }

    checkBytes<uint16_t>(ran);
    checkBytes<uint32_t>(ran);
    checkBytes<uint64_t>(ran);



}
Y_UDONE()
