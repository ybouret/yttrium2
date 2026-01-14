#include "y/stream/bzip2/input.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;


Y_UTEST(stream_bzip2_read)
{
    if(argc>1)
    {
        BZip2::InputFile fp( argv[1] );
        String line;
        while( fp.gets(line) )
        {
            std::cerr << line << std::endl;
        }

    }
}
Y_UDONE()

