#include "y/stream/gzip/input.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

Y_UTEST(stream_gzip_read)
{
    if(argc>1)
    {
        GZip::Input input( argv[1] );
        String line;
        while( input.gets(line) )
            std::cerr << line << std::endl;
    }
}
Y_UDONE()
