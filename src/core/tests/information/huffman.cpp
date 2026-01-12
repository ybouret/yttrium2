
#include "y/utest/run.hpp"
#include "y/information/pack/huffman.hpp"

#include "y/stream/libc/input.hpp"

using namespace Yttrium;



Y_UTEST(info_huffman)
{
    Information::Pack::Alphabet streaming( Information::Pack::Streaming );
    Information::Pack::Alphabet messaging( Information::Pack::Messaging );
    Information::Pack::Huffman  huff;

    streaming.display(std::cerr);

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

    streaming.display(std::cerr);
    std::cerr << "swaps=" << huff.pq.nswp() << std::endl;

    Vizible::Render("huff.dot", *huff.root);


}
Y_UDONE()

