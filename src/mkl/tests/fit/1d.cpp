#include "y/mkl/fit/raw-sample.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(fit_1d)
{
    Fit::Parameters params;
    params << "t0" << "D1" << "D2";

    std::cerr << "params=" << params << std::endl;
}
Y_UDONE()

