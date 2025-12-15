
#include "y/mkl/fit/spec/polynomial.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/sorting/heap.hpp"

using namespace Yttrium;
using namespace MKL;

static void testFitPoly(XMLog &xml,
                        Fit::Optimizer<double> &fit,
                        Fit::Sample<double,double> &data,
                        const Fit::Polynomial::Coefficients &coef,
                        const char * const                   info)
{
    Fit::Polynomial::Session<double> poly(coef);
    (void)poly(xml,fit,data);
    data.save(data.name + "-" + info + ".dat");
}

Y_UTEST(fit_poly)
{

    Random::ParkMiller            ran;



    Vector<double> X;
    Vector<double> Y;
    Vector<double> Yf;

    for(size_t i=10+ran.leq<unsigned>(20); i>0; --i)
    {
        const double x = ran.to<double>() * 1.6;
        X  << x;
        Y  << sin(x) + 0.01*ran.symm<double>();
        Yf << 0.0;
    }
    

    X.hsort( Sign::Increasing<double>, Y );

    bool  verbose = true;
    XMLog xml(std::cerr,verbose);
    Fit::Optimizer<double> fit;
    Fit::Sample<double,double> data("poly.fit",X,Y,Yf);

    data.save(data.name);

#if 1
    {
        Fit::Polynomial::Coefficients constant("a");
        constant << 0;
        testFitPoly(xml,fit,data,constant, "constant");
    }

    {
        Fit::Polynomial::Coefficients linear("a");
        linear << 1;;
        testFitPoly(xml,fit,data,linear,"linear");
    }

    {
        Fit::Polynomial::Coefficients affine("a");
        affine << 0 << 1;
        testFitPoly(xml,fit,data,affine,"affine");
    }

    {
        Fit::Polynomial::Coefficients quad("a");
        quad << 0 << 1 << 2;
        testFitPoly(xml,fit,data,quad,"quad");
    }
#endif


}
Y_UDONE()


