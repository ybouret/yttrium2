
#include "y/mkl/statistics/descriptive.hpp"
#include "y/utest/run.hpp"
#include "y/system/rtti.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/sequence/list.hpp"

#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif
#include "../../core/tests/main.hpp"


using namespace Yttrium;
using namespace MKL;


template <typename T> static inline
void TestDescriptive(Random::Bits &ran)
{
    std::cerr << std::endl;

    Statistics::Descriptive<T> sd;

    Vector<T> v;
    List<T>   l;

    for(size_t i = ran.leq<size_t>(100);i>0;--i)
    {
        const T x = Gen<T>::New(ran);
        v << x;
        l << x;
    }

    const T v_ave = sd.average(v);
    const T l_ave = sd.average(l);

    std::cerr << "v_ave=" << v_ave << std::endl;
    std::cerr << "l_ave=" << l_ave << std::endl;

    const T v_var = sd.variance(v,v_ave);
    const T l_var = sd.variance(l,l_ave);

    std::cerr << "v_var=" << v_var << std::endl;
    std::cerr << "l_var=" << l_var << std::endl;

    const T v_sdev = sd.stddev(v,v_ave);
    const T l_sdev = sd.stddev(l,l_ave);

    std::cerr << "v_sdev=" << v_sdev << std::endl;
    std::cerr << "l_sdev=" << l_sdev << std::endl;

    const T v_adev = sd.absdev(v,v_ave);
    const T l_adev = sd.absdev(l,l_ave);

    std::cerr << "v_adev=" << v_adev << std::endl;
    std::cerr << "l_adev=" << l_adev << std::endl;

    const T v_skew = sd.skewness(v,v_ave,v_sdev);
    const T l_skew = sd.skewness(l,l_ave,l_sdev);

    std::cerr << "v_skew=" << v_skew << std::endl;
    std::cerr << "l_skew=" << l_skew << std::endl;

    const T v_kurt = sd.kurtosis(v,v_ave,v_sdev);
    const T l_kurt = sd.kurtosis(l,l_ave,l_sdev);

    std::cerr << "v_kurt=" << v_kurt << std::endl;
    std::cerr << "l_kurt=" << l_kurt << std::endl;

}


Y_UTEST(statistics_descriptive)
{

    Random::MT19937 ran;

    TestDescriptive<float>(ran);

    TestDescriptive< XReal<float> >(ran);

}
Y_UDONE()

