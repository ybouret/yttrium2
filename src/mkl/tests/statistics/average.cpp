#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(statistics_average)
{
    Cameo::Addition<float> xadd;
    std::cerr << xadd->size() << std::endl;
    xadd << 1.0f;
    std::cerr << xadd->size() << std::endl;
    xadd << 3.0f;
    std::cerr << xadd->size() << std::endl;
    

}
Y_UDONE()

