#include "y/rtld/dll.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(rtld)
{
    if(argc>1)
    {
        const DLL dll = argv[1];
        for(int i=2;i<argc;++i)
        {
            const char * const symbol = argv[i];
            void * const addr = dll.query(symbol);
            std::cerr << symbol << " @" << addr << std::endl;
        }

    }
}
Y_UDONE()
