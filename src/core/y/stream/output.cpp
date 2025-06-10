

#include "y/stream/output.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/calculus/alignment.hpp"
#include "y/hexadecimal.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    OutputStream:: ~OutputStream() noexcept
    {
    }

    OutputStream:: OutputStream() noexcept
    {
    }


    size_t OutputStream:: encode64(uint64_t qw)
    {
        static const unsigned AvailableMask[9] =
        {
            0, 1, 3, 7, 15, 31, 63, 127, 255
        };

        static const unsigned MaxInputBytes  = sizeof(uint64_t);
        static const unsigned MaxInputBits   = 8 * MaxInputBytes;
        static const unsigned MaxOutputBytes = MaxInputBytes+1;
        static const unsigned HeaderBits     = IntegerLog2<MaxInputBytes>::Value+1;
        static const unsigned HeaderRoll     = 8-HeaderBits;

        const unsigned inputBits   = Calculus::BitsFor::Count(qw);
        const unsigned outputBits  = HeaderBits + inputBits;
        const size_t   outputBytes = Alignment::On<8>::Ceil(outputBits)/8;
        std::cerr << "inputBits   = " << inputBits << std::endl;
        std::cerr << "outputBits  = " << outputBits << std::endl;
        std::cerr << "outputBytes = " << outputBytes << std::endl;

        assert(BitsFor(outputBytes) <= HeaderBits );

        uint8_t b = static_cast<uint8_t>(outputBytes << HeaderRoll); assert( unsigned(b>>HeaderRoll) == outputBytes );

        unsigned  available = HeaderRoll;
        unsigned  remaining = inputBits;

        if( remaining <= available )
        {
            b |= uint8_t(qw);
            write(b);
            return 1;
        }

        throw Exception("not implemented");


#if 0
        while(remaining>available)
        {
            assert(available>0);
            assert(available<=8);
            b |= AvailableMask[available] & qw;
            write(b);
            ++n;
            qw       >>= available;
            remaining -= available;
            assert( Calculus::BitsFor::Count(qw) == remaining);
            available  = 8;
            b          = 0;
        }
#endif



        return 0;
    }


}

