
#include "y/mkl/fit/spec/polynomial.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/sorting/heap.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(fit_poly)
{

    Random::ParkMiller ran;
    Fit::Polynomial::Coefficients coef("a");

    coef << 0 << 1;

    std::cerr << coef << std::endl;


    Vector<double> X;
    Vector<double> Y;
    Vector<double> Yf;

    for(size_t i=10+ran.leq<unsigned>(20); i>0; --i)
    {
        const double x = ran.to<double>() * 2.0;
        X  << x;
        Y  << sin(x) + 0.01*ran.symm<double>();
        Yf << 0.0;
    }

    X.hsort( Sign::Increasing<double>, Y );


    Fit::Sample<double,double> data("poly.fit",X,Y,Yf);
    data.save(data.name);

    Fit::Polynomial::Session<double> poly(coef);


}
Y_UDONE()


