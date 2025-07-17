#include "y/mkl/xreal.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;


Y_UTEST(mkl_xreal)
{
    XReal<float> x = 3;
    std::cerr << double(x) << std::endl;
    x.shr();
    std::cerr << double(x) << std::endl;

}
Y_UDONE()
