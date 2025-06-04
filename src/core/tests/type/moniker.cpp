
#include "y/type/moniker.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(type_moniker)
{

    Moniker<long double> x = 0.1L;

    std::cerr << "x=" << x << std::endl;

}
Y_UDONE()
