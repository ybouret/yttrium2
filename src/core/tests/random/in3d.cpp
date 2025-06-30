

#include "y/random/in3d.hpp"
//#include "y/mkl/v2d.hpp"

#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace {



}


Y_UTEST(random_in3d)
{

    Random::ParkMiller ran;

    double x=0,y=0,z=0;
    Random::OnSphere(x,y,z,ran);
    std::cerr << x << "," << y << "," << z << " : " << (x*x+y*y+z*z) << std::endl;

    XReal<long double> X, Y, Z;
    Random::OnSphere(X,Y,Z,ran);
    std::cerr << X << "," << Y << "," << Z << " : " << (X*X+Y*Y+Z*Z) << std::endl;


}
Y_UDONE()

