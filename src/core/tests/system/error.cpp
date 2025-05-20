#include "y/utest/run.hpp"
#include "y/system/error.hpp"

using namespace Yttrium;

Y_UTEST(system_error)
{
    Y_SIZEOF(System::Error::Type);
    for(int i=1;i<argc;++i)
    {
        std::cerr << "argv[" << i << "] = " << argv[i] << std::endl;
    }
    
    char buffer[256];
    for(int err=0;err<10;++err)
    {
        std::cerr << System::Error::Format(buffer,sizeof(buffer),System::Error::Type(err)) << std::endl;
    }
}
Y_UDONE()


