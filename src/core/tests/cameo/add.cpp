#include "y/cameo/summator.hpp"
#include "y/cameo/summator/fpoint.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"


#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

#include "y/check/static.hpp"

using namespace Yttrium;

namespace Yttrium
{

    namespace Cameo
    {

        
     

    }


}

Y_UTEST(cameo_add)
{

    Cameo::DirectSummator<apz> zsum;
    Cameo::DirectSummator<apn> nsum;

    Cameo::AProxySummator<int>            isum; std::cerr << "isum/" <<Cameo::AProxySummator<int>::CoreType::CallSign << std::endl;
    Cameo::AProxySummator<unsigned short> usum; std::cerr << "usum/" <<Cameo::AProxySummator<unsigned short>::CoreType::CallSign << std::endl;

    Y_SIZEOF(Cameo::FPointSummator<float>::Accumulator);
    Y_SIZEOF(Cameo::FPointSummator< XReal<long double> >::Accumulator);


}
Y_UDONE()



