
#include "y/mkl/api/fcpu.hpp"
#include "y/utest/run.hpp"
#include "y/system/rtti.hpp"


using namespace Yttrium;
using namespace MKL;

template <typename T> static inline
void ShowFCPU()
{
    std::cerr << "FCPU<" << std::setw(16) << System::RTTI::Name<T>() << "  > = ";
    typedef typename FCPU<T>::Type fcpu_t;
    std::cerr << System::RTTI::Name<fcpu_t>();
    std::cerr << std::endl;
}

Y_UTEST(mkl_fcpu)
{
    ShowFCPU< float >();
    ShowFCPU< XReal<float> >();
    ShowFCPU< double >();
    ShowFCPU< XReal<double> >();
}
Y_UDONE()
