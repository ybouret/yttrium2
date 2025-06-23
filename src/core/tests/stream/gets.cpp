


#include "y/stream/libc/input.hpp"
#include "y/string.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(stream_gets)
{
    if(argc>1)
    {
        InputFile fp(argv[1]);
        String    s;
        while( fp.gets(s) )
            std::cerr << '[' << s << ']' << std::endl;
    }
}
Y_UDONE()
