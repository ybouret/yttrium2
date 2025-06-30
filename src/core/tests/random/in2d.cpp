
#include "y/random/in2d.hpp"
//#include "y/mkl/v2d.hpp"

#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace {



}


Y_UTEST(random_in2d)
{

    Random::ParkMiller ran;

    double x=0,y=0;
    Random::OnCircle(x,y,ran);
    std::cerr << x << "," << y << ": " << (x*x+y*y) << std::endl;

    XReal<long double> X, Y;
    Random::OnCircle(X,Y,ran);
    std::cerr << X << "," << Y << ": " << (X*X+Y*Y) << std::endl;


}
Y_UDONE()

