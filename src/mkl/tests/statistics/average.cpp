#include "y/mkl/statistics/average.hpp"
#include "y/utest/run.hpp"
#include "y/system/rtti.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif
#include "../../core/tests/main.hpp"


using namespace Yttrium;
using namespace MKL;


template <typename T> static inline
void TestAverage(Random::Bits &ran)
{
    std::cerr << std::endl;

    Statistics::Average<T> average;
    std::cerr << "type: " << System::RTTI::Name<T>() << std::endl;
    std::cerr << "fcpu: " << System::RTTI::Name<typename  Statistics::Average<T>::fcpu_t> () << std::endl;

}


Y_UTEST(statistics_average)
{

    Random::MT19937 ran;

    TestAverage<float>(ran);
    TestAverage< XReal<float> >(ran);
    TestAverage< Complex<double> >(ran);

}
Y_UDONE()

