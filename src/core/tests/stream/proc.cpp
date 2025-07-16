
#include "y/stream/proc/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_proc)
{

    for(int i=1;i<argc;++i)
    {
        const String cmd = argv[i];
        InputProcess inp(cmd);
        String line;
        while( inp.gets(line) )
        {
            std::cerr << "[+] " << line << std::endl;
        }
    }

}
Y_UDONE()

