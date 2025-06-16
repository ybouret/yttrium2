#include "y/utf8/api.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"
#include "y/binary.hpp"

using namespace Yttrium;

Y_UTEST(utf8_api)
{
    Y_PRINTV( UTF8::MaxCodePoint );


    for(size_t i=0;i<UTF8::Count;++i)
    {
        std::cerr << "Bits: " << BitsFor(UTF8::Table[i].tail) << std::endl;
    }



    {
        const uint32_t cp = 0xC0; // accentued A
        const UTF8::Encoding enc(cp);
        std::cerr << enc << std::endl;
        Y_CHECK(2==enc.size);
        Y_CHECK(0xC3==enc.byte[0]);
        Y_CHECK(0x80==enc.byte[1]);
    }

    {
        const uint32_t       cp = 0x20AC; // euro
        const UTF8::Encoding enc(cp);
        std::cerr << enc << std::endl;
        Y_CHECK(3==enc.size);
        Y_CHECK(0xE2==enc.byte[0]);
        Y_CHECK(0x82==enc.byte[1]);
        Y_CHECK(0xAC==enc.byte[2]);

    }

    {
        const uint32_t       cp = 0x1D11E; // G key
        const UTF8::Encoding enc(cp);
        std::cerr << enc << std::endl;
        Y_CHECK(4==enc.size);
        Y_CHECK(0xF0==enc.byte[0]);
        Y_CHECK(0x9D==enc.byte[1]);
        Y_CHECK(0x84==enc.byte[2]);
        Y_CHECK(0x9E==enc.byte[3]);
    }

    for(uint32_t i=0;i<UTF8::MaxCodePoint;++i)
    {
        const UTF8::Encoding enc(i);
    }


}
Y_UDONE()

