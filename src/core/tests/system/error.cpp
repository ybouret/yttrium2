#include "y/utest/run.hpp"
#include "y/system/error.hpp"
#include <iostream>

using namespace Yttrium;

Y_UTEST(error)
{
    char buffer[256];
    for(int err=0;err<10;++err)
    {
        std::cerr << System::Error::Format(buffer,sizeof(buffer),System::Error::Type(err)) << std::endl;
    }
}
Y_UDONE()

void testError()
{
    char buffer[256];
    for(int err=0;err<10;++err)
    {
        std::cerr << System::Error::Format(buffer,sizeof(buffer),System::Error::Type(err)) << std::endl;
    }
}
