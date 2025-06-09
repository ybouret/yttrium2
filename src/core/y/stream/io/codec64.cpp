#include "y/stream/io/codec64.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/calculus/alignment.hpp"
#include "y/hexadecimal.hpp"


namespace Yttrium
{

    namespace IO
    {

        Codec64:: ~Codec64() noexcept
        {
        }

        Codec64:: Codec64(const uint64_t qw) noexcept : byte()
        {
            static const uint64_t mask[] =
            {

            };

            const unsigned inputBits   = Calculus::BitsFor::Count(qw);
            const unsigned outputBits  = HeaderBits + inputBits;
            const size_t   outputBytes = Alignment::On<8>::Ceil(outputBits)/8;
            std::cerr << "inputBits   = " << inputBits << std::endl;
            std::cerr << "outputBits  = " << outputBits << std::endl;
            std::cerr << "outputBytes = " << outputBytes << std::endl;

            assert(BitsFor(outputBytes) <= HeaderBits );

            // write header
            byte[0] = static_cast<uint8_t>(outputBytes << HeaderRoll); assert( (byte[0]>>HeaderRoll) == outputBytes );

            Hexadecimal::Display(std::cerr,byte,1) << std::endl;

            unsigned  available = HeaderRoll;
            unsigned  remaining = inputBits;
            uint8_t * objective = byte;
            
        }


    }

}

