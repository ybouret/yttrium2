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
        const uint32_t cp = 0x20AC; // euro
        const UTF8::Encoding enc(cp);
        std::cerr << enc << std::endl;
        Y_CHECK(3==enc.size);
        Y_CHECK(0xE2==enc.byte[0]);
        Y_CHECK(0x82==enc.byte[1]);
        Y_CHECK(0xAC==enc.byte[2]);

    }


    return 0;
    
    for(uint32_t i=0;i<UTF8::MaxCodePoint;++i)
    {
        const UTF8::Encoding enc(i);
    }
#if 0
    const uint32_t       euro_cp  = 0x20AC;
    const UTF8::Encoding euro_utf(euro_cp);
    std::cerr << (char *)euro_utf.byte << std::endl;
#endif

}
Y_UDONE()

