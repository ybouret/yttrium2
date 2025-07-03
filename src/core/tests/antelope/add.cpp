#include "y/mkl/api/pythagoras.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(antelope_add)
{
    std::cerr << MKL::Pythagoras<float>(3,4) << std::endl;
}
Y_UDONE()



