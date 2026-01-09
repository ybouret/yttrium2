
#include "y/utest/run.hpp"
#include "y/information/pack/huffman.hpp"

#include "y/stream/libc/input.hpp"

using namespace Yttrium;



Y_UTEST(info_huffman)
{
    Information::Pack::Alphabet streaming( Information::Pack::Streaming );
    Information::Pack::Alphabet messaging( Information::Pack::Messaging );
    Information::Pack::Huffman  huff;

    if(argc>1)
    {
        InputFile fp( argv[1] );
        char      c = 0;

        while( fp.query(c) )
        {
            const uint8_t b = c;
            streaming << b;
            messaging << b;

            huff.build(streaming);
        }


    }





}
Y_UDONE()

