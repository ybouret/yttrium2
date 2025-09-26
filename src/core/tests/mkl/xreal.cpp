#include "y/mkl/xreal.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/api/fpow.hpp"

using namespace Yttrium;


Y_UTEST(mkl_xreal)
{
    XReal<float> x = 3;
    const float  X = float(x);
    std::cerr << MKL::Fpow<float>::Of(X,2) << std::endl;
    std::cerr << MKL::Fpow< XReal<float> >::Of(x,2) << std::endl;

    std::cerr << double(x) << std::endl;
    x.shr();
    std::cerr << double(x) << std::endl;



}
Y_UDONE()
