

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
        static const size_t   MaxExtraBytes = 8;
        static const size_t   HeaderBits    = IntegerLog2<MaxExtraBytes>::Value + 1;
        static const size_t   HeaderRoll    = 8 - HeaderBits;
        static const uint64_t HeaderMask    = (1<<HeaderRoll)-1;

        std::cerr << "HeaderBits=" << HeaderBits << std::endl;
        std::cerr << "HeaderRoll=" << HeaderRoll << std::endl;
        std::cerr << "HeaderMask=" << HeaderMask << std::endl;

        size_t       inputBits = Calculus::BitsFor::Count(qw);
        const size_t totalBits = inputBits + HeaderBits;
        const size_t totalSize = Alignment::On<8>::Ceil(totalBits) >> 3;
        const size_t extraSize = totalSize-1;
        assert(totalSize>=1);
        assert(totalSize<=1+MaxExtraBytes);

        std::cerr << "inputBits = " << inputBits << std::endl;
        std::cerr << "totalBits = " << totalBits << std::endl;
        std::cerr << "totalSize = " << totalSize << std::endl;

        if(inputBits<=HeaderRoll)
        {
            assert(0==extraSize);
            write( (uint8_t(extraSize) << HeaderRoll) | uint8_t(qw) );
            return 1;
        }

        uint8_t byte[9];
        byte[0] = (uint8_t(extraSize) << HeaderRoll) | uint8_t(qw&HeaderMask);

        inputBits -= HeaderRoll;
        qw       >>= HeaderRoll;
        assert( Calculus::BitsFor::Count(qw) == inputBits );
        assert( inputBits <= extraSize * 8);

        {
            uint8_t *p = byte;
            ++p;
            while(inputBits>=8)
            {
                *(p++) = uint8_t(qw);
                qw       >>= 8;
                inputBits -= 8;
            }
            assert( Calculus::BitsFor::Count(qw) < 8);
            *p = uint8_t(qw); // may be 0
        }

        for(size_t i=0;i<totalSize;++i)
        {
            write(byte[i]);
        }
        return totalSize;
    }


}

