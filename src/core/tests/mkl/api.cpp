
#include "y/mkl/api/selector.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/complex.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    static inline void DisplayAPI()
    {
        static const typename MKL::API_Select<T>::Choice choice =  {};
        std::cerr << "Value=" << choice.Value << std::endl;
    }
}

Y_UTEST(mkl_api)
{

    DisplayAPI<int>();
    DisplayAPI<long double>();
    DisplayAPI< Complex<float> >();

}
Y_UDONE()
