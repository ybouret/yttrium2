
#include "y/information/bwt/bwt.hpp"
#include "y/information/stream/move-to-front.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"
#include "y/core/text.hpp"
#include "y/hexadecimal.hpp"
#include <cassert>
#include <cstring>

using namespace Yttrium;

Y_UTEST(info_bwt)
{

    static const size_t smax = 1023;
    char   encoded[smax+1];
    char   decoded[smax+1];
    char   reworkd[smax+1];
    size_t indices[smax+1];

    Information::MoveToFront::Encoder mtf;
    for(int i=1;i<argc;++i)
    {
        const char * const input = argv[i]; assert(0!=input);
        const size_t       size  = Core::Text::Length(input);
        if(size>smax) continue;

        std::cerr << input << std::endl;
        Y_Memory_BZero(encoded);
        const size_t primary = Information::BWT::Encode(encoded,input,size,indices);
        std::cerr << encoded << " @" << primary << std::endl;
        Y_Memory_BZero(decoded);
        Information::BWT::Decode(decoded,encoded,size,indices,primary);
        std::cerr << decoded << std::endl;
        Y_ASSERT( 0 == memcmp(input,decoded,size) );

        Y_Memory_BZero(reworkd);
        mtf.restart();
        mtf.transform(reworkd,encoded,size);
        Hexadecimal::Display(std::cerr,input,size)   << std::endl;
        Hexadecimal::Display(std::cerr,encoded,size) << std::endl;
        Hexadecimal::Display(std::cerr,reworkd,size) << std::endl;
    }



}
Y_UDONE()

