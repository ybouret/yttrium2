#include "y/information/codec/rle/compress.hpp"
#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(info_rle)
{
    Information::RLE::Compress rle;

    if( argc > 1 )
    {
        {
            InputFile fp(argv[1]);
            char c = 0;
            while( fp.query(c) )
                rle.write(c);
        }

        {
            OutputFile fp("rle.dat");
            char c;
            while(rle.query(c))
                fp.write(c);

        }
    }
}
Y_UDONE()

