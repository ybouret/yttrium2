#include "y/stream/bzip2/file/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(stream_bzip2_read)
{
    if(argc>1)
    {
        BZip2::InputFile fp( argv[1] );

    }
}
Y_UDONE()

