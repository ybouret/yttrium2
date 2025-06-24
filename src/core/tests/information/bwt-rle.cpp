
#include "y/information/codec/rle/compress.hpp"
#include "y/information/bwt/transformer.hpp"
#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

Y_UTEST(info_bwt_rle)
{

    Information::BWT_Transformer bwt;
    //Concurrent::Singulet::Verbose = true;
    Information::RLE::Compress rle;
    Vector<char>               source;
    
    if( argc > 1 )
    {
        {
            InputFile fp(argv[1]);
            char c = 0;
            while( fp.query(c) )
                source << c;
        }

        const size_t length = source.size();
        Vector<char> target(length,0);
        const size_t primary = bwt.encode( target(), source(), length);
        std::cerr << "primary=" << primary << "/" << length << std::endl;

        rle.reset();
        rle.frame(target(),length);
        rle.flush();
        
        {
            OutputFile fp("rle.dat");
            char c;
            while( rle.query(c) ) fp.write(c);

        }
    }
}
Y_UDONE()

