
#include "y/cameo/multiplier/aproxy.hpp"
#include "y/cameo/multiplier/direct.hpp"

#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;


Y_UTEST(cameo_mul)
{
    {
        Cameo::DirectMultiplier<apn> nmul;
        Cameo::DirectMultiplier<apz> zmul;
        Cameo::DirectMultiplier<apq> qmul;
    }

    {
        Cameo::AProxyMultiplier<int> imul;
    }
}
Y_UDONE()
