
#include "y/utest/run.hpp"
#include "y/information/pack/huffman.hpp"

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/io/bits.hpp"

using namespace Yttrium;



Y_UTEST(info_huffman)
{
    Information::Pack::Alphabet streaming( Information::Pack::Streaming );
    Information::Pack::Alphabet messaging( Information::Pack::Messaging );
    Information::Pack::Huffman  huff;
    OutputFile out("huff.dat");
    IO::Bits   bits,pool;

    streaming.display(std::cerr);
    size_t numInp = 0;
    size_t numOut = 0;

    if(argc>1)
    {
        InputFile inp( argv[1] );
        char      c = 0;

        while( inp.query(c) )
        {
            ++numInp;
            const uint8_t b = c;
            bits.push(streaming.database[b].code,streaming.database[b].bits,pool);
            std::cerr << bits << std::endl;
            streaming << b;
            messaging << b;
            huff.build(streaming);
            numOut += bits.write(out,pool);
        }
    }
    std::cerr << "flushing " << bits << std::endl;
    numOut += bits.flush(out,pool);

    streaming.display(std::cerr);
    std::cerr << "swaps=" << huff.pq.nswp() << std::endl;

    Vizible::Render("huff.dot", *huff.root);
    std::cerr << "data: " << numInp << " => " << numOut << std::endl;

}
Y_UDONE()

