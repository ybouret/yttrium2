
#include "y/mkl/fit/spec/polynomial.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(fit_poly)
{

    Fit::Polynomial::Coefficients coef("a");

    coef << 0 << 1;

    std::cerr << coef << std::endl;
}
Y_UDONE()


