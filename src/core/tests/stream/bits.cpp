#include "y/stream/io/bits.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/string.hpp"

#include "y/stream/libc/output.hpp"

using namespace Yttrium;

Y_UTEST(stream_io_bits)
{
    IO::Bits bits,pool;

    bits.push<uint8_t>(0xab,6,pool);
    std::cerr << bits << std::endl;
    const uint8_t b = bits.pop<uint8_t>(4,pool);
    std::cerr << Hexadecimal(b) << std::endl;
    std::cerr << bits << std::endl;
    bits.to(pool);
    std::cerr << bits << std::endl;

    std::cerr << bits.push<uint16_t>(0xab,pool) << std::endl;
    Y_ASSERT(16==bits->size);
    for(size_t i=1;i<=8;++i)
    {
        const uint16_t x = bits.peek<uint16_t>(i);
        std::cerr << Hexadecimal(x,Concise) << std::endl;
    }

    bits.to(pool);
    std::cerr << "#pool = " << pool->size << std::endl;

    const String s = "Hello, World!";
    for(size_t i=1;i<=s.size();++i)
    {
        bits.push<uint8_t>( (uint8_t)s[i], pool);
    }
    std::cerr << bits << std::endl;
    {
        OutputFile fp("bits.dat");
        bits.write(fp,pool);
    }
    std::cerr << "#pool = " << pool->size << std::endl;



}
Y_UDONE()


