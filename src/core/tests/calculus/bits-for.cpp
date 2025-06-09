
#include "y/calculus/bits-for.hpp"
#include "y/utest/run.hpp"

#include "y/hexadecimal.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    static unsigned CountBitsFor(const uint64_t u) noexcept
    {
        switch(u)
        {
            case 0:
                return 0;

            case 1:
                return 1;

            default:
                break;
        }
        uint64_t mask = 0x1ULL << 63;
        unsigned bits = 64;
        while(0==(mask&u))
        {
            --bits;
            mask>>=1;
        }
        return bits;
    }
}

Y_UTEST(calculus_bits_for)
{
    System::Rand ran;

    if(false)
    {
        unsigned u = 0x00;
        for(unsigned i=0;i<16;++i)
        {
            for(unsigned j=0;j<16;++j,++u)
            {
                const unsigned res = CountBitsFor(u);
                std::cerr << ' ' << res << ',';
            }
            std::cerr << std::endl;
        }
    }

    std::cerr << "Check 8-bits" << std::endl;
    for(uint64_t i=0;i<256;++i)
    {
        const uint8_t u = uint8_t(i);
        Y_ASSERT( CountBitsFor(u) == Calculus::BitsFor::Count(u) );
    }

    std::cerr << "Check 16-bits" << std::endl;
    for(uint64_t i=0;i<65536;++i)
    {
        const uint16_t w = uint16_t(i);
        Y_ASSERT( CountBitsFor(w) == Calculus::BitsFor::Count(w) );
    }


    std::cerr << "Check 32-bits" << std::endl;
    for(unsigned nbit=0;nbit<=32;++nbit)
    {
        //std::cerr << "|bits|=" << nbit << std::endl;
        for(unsigned iter=0;iter<16;++iter)
        {
            const uint32_t dw = ran.gen<uint32_t>(nbit);
            //std::cerr << "\t=> " << Hexadecimal(dw) << std::endl;
            Y_ASSERT(Calculus::BitsFor::Count(dw) == nbit);
        }
    }

    std::cerr << "Check 64-bits" << std::endl;
    for(unsigned nbit=0;nbit<=64;++nbit)
    {
        //std::cerr << "|bits|=" << nbit << std::endl;
        for(unsigned iter=0;iter<16;++iter)
        {
            const uint64_t qw = ran.gen<uint64_t>(nbit);
            //std::cerr << "\t=> " << Hexadecimal(qw) << std::endl;
            Y_ASSERT(Calculus::BitsFor::Count(qw) == nbit);
        }
    }

}
Y_UDONE()

