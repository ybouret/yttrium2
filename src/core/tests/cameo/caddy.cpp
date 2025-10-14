


#include "y/cameo/caddy.hpp"
#include "y/utest/run.hpp"
#include "y/system/rtti.hpp"

using namespace Yttrium;

Y_UTEST(cameo_caddy)
{
    Cameo::Caddy<float> caddy;
    caddy.adjust(4);
    
}
Y_UDONE()

