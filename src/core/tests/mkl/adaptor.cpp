
#include "y/mkl/api/adaptor.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace MKL;

namespace
{

}

Y_UTEST(mkl_adaptor)
{
    
    const TypeToType<double> DoubleType = {};


    int a  = 2;
    std::cerr << MKL::AdaptedTo(DoubleType,a) << std::endl;
    double x = 3;
    std::cerr << MKL::AdaptedTo(DoubleType,x) << std::endl;


}
Y_UDONE()

