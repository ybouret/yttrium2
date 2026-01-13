

#include "y/utest/run.hpp"
#include "y/information/pack/huffman.hpp"
#include "y/information/stream/verbatim.hpp"
#include "y/information/stream/move-to-front.hpp"
#include "y/information/stream/delta.hpp"

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/io/bits.hpp"


using namespace Yttrium;

namespace
{
    struct XAlpha
    {
        Information::Pack::Alphabet &alpha;
        Information::StreamCipher   &cipher;
        OutputStream                &output;
        IO::Bits                    &bits;
        size_t                       written;
    };
}

Y_UTEST(info_huffenc)
{
    
    Information::Pack::Alphabet vbtAlpha( Information::Pack::Streaming );
    Information::Pack::Alphabet mtfAlpha( Information::Pack::Streaming );
    Information::Pack::Alphabet delAlpha( Information::Pack::Streaming );

    Information::Verbatim::Encoder    vbt;
    Information::MoveToFront::Encoder mtf;
    Information::Delta::Encoder       del;

    IO::Bits   vbtBits, mtfBits, delBits, pool;

    OutputFile vbtOut("vbt.dat");
    OutputFile mtfOut("mtf.dat");
    OutputFile delOut("del.dat");


    XAlpha xalpha[] =
    {
        { vbtAlpha, vbt, vbtOut, vbtBits, 0 },
        { mtfAlpha, mtf, mtfOut, mtfBits, 0 },
        { delAlpha, del, delOut, delBits, 0 }
    };
    const size_t xcount = sizeof(xalpha)/sizeof(xalpha[0]);

    Information::Pack::Huffman        huff;
    size_t input = 0;
    if(argc>1)
    {
        InputFile fp(argv[1]);
        char      c = 0;
        while(fp.query(c))
        {
            const uint8_t src = (uint8_t)c;
            ++input;
            for(size_t i=0;i<xcount;++i)
            {
                XAlpha &xa = xalpha[i];
                const uint8_t tgt = xa.cipher(src);

                // emit current model
                xa.alpha.emit(xa.bits,tgt,pool);
                // update model
                xa.alpha << tgt; huff.build(xa.alpha);
                // progressive writing
                xa.written += xa.bits.write(xa.output,pool);
            }
        }
    }

    std::cerr << "input: " << input << std::endl;
    for(size_t i=0;i<xcount;++i)
    {
        XAlpha &xa = xalpha[i];
        xa.written += xa.bits.flush(xa.output,pool);
        std::cerr << " " << xa.written << std::endl;
    }



}
Y_UDONE()

