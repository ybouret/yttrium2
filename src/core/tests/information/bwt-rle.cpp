
#include "y/information/codec/rle/compress.hpp"
#include "y/information/bwt/transformer.hpp"
#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

Y_UTEST(info_bwt_rle)
{
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

        {
            OutputFile fp("rle.dat");
            //fp.frame(source(),source.size());
        }
    }
}
Y_UDONE()

