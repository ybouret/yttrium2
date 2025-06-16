#include "y/utf8/api.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"
#include "y/binary.hpp"

using namespace Yttrium;

Y_UTEST(utf8_api)
{
    Y_PRINTV( UTF8::MaxCodePoint );






    {
        const uint32_t cp = 0xC0;
        const UTF8::Encoding enc(cp);
        std::cerr << enc << std::endl;
        std::cerr << Binary(enc.byte[0]) << ' ' << Binary(enc.byte[1]) << std::endl;
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

