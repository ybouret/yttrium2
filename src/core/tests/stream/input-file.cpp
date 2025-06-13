

#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(stream_input_file)
{
    if(argc>1)
    {
        InputFile fp(argv[1]);
        char C;
        while( fp.query(C) )
            std::cerr << C;
    }
}
Y_UDONE()
