
#include "y/utest/run.hpp"
#include "y/information/pack/huffman.hpp"

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/io/bits.hpp"

#include "y/random/park-miller.hpp"

using namespace Yttrium;

static inline void TestHuffFull()
{
    Random::ParkMiller ran;
    Information::Pack::Alphabet streaming( Information::Pack::Streaming );
    Information::Pack::Alphabet messaging( Information::Pack::Messaging );
    Information::Pack::Huffman  huff;

    streaming.reset();
    messaging.reset();
    for(unsigned i=0;i<256;++i)
    {
        const uint8_t b = (uint8_t)i;
        for(size_t j = ran.in<size_t>(1,8);j>0;--j)
            streaming << b;
        for(size_t j = ran.in<size_t>(1,8);j>0;--j)
            messaging << b;
    }

    std::cerr << "build streaming" << std::endl;
    huff.build(streaming);
    std::cerr << "build messagin" << std::endl;
    huff.build(messaging);


}

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
    std::cerr << "swaps=" << huff.Q->nswp << std::endl;

    if(huff.root)
        Vizible::Render("huff.dot", *huff.root);
    std::cerr << "data: " << numInp << " => " << numOut << std::endl;

    TestHuffFull();

    Y_SIZEOF(Information::Pack::Huffman::Node);
    Y_PRINTV(Information::Pack::Huffman::InnerNodes);
    Y_PRINTV(Information::Pack::Huffman::InnerBytes);
    Y_PRINTV(Information::Pack::Huffman::InnerWords);
    Y_SIZEOF(Information::Pack::Huffman);
    

}
Y_UDONE()

