#include "y/information/entropy.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(info_entropy)
{
    Information::Entropy S;

    for(int i=1;i<argc;++i)
    {
        S << argv[i];
    }

    std::cerr << "S=" << S() << std::endl;

}
Y_UDONE()
