

#include "y/ink/pixmap.hpp"
#include "y/utest/run.hpp"
#include "../../core/tests/main.hpp"

using namespace Yttrium;
using namespace Ink;

Y_UTEST(pixmap)
{
    Random::MT19937 ran;


    Pixmap<String> p(10,8);

    for(unit_t j=0;j<p.upper.y;++j)
    {
        for(unit_t i=0;i<p.upper.x;++i)
        {
            p[j][i] = Gen<String>::New(ran);
        }
    }



}
Y_UDONE()
