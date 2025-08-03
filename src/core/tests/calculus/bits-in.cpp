#include "y/calculus/bits-in.hpp"
#include "y/utest/run.hpp"
using namespace Yttrium;

namespace

{

    static inline unsigned CountBitsIn(const uint8_t b)
    {
        static const uint8_t bit[8] = {1,2,4,8,16,32,64,128};
        unsigned sum = 0;
        for(unsigned i=0;i<8;++i)
        {
            if( 0 != (b&bit[i])) ++sum;
        }
        return sum;
    }
}


Y_UTEST(calculus_bits_in)
{

    uint8_t k = 0;
    for(unsigned i=0;i<16;++i)
    {
        for(unsigned j=0;j<16;++j,++k)
        {
            std::cerr << " " << CountBitsIn(k) << ",";
        }
        std::cerr << std::endl;
    }

}
Y_UDONE()

