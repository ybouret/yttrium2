
#include "y/calculus/iabs.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_iabs)
{

    std::cerr << IntegerAbs<int>( -10 ) << std::endl;
    std::cerr << IntegerAbs<uint64_t>( 10 ) << std::endl;



}
Y_UDONE()

