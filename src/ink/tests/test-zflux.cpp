


#include "y/ink/zero-flux.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

using namespace Yttrium;
using namespace Ink;

Y_UTEST(zflux)
{
    OutputFile fp("zflux.dat");

    for(int i=-10; i<=20;++i)
    {
        fp("%d",i);
        for(unsigned n=1;n<=10;++n)
        {
            ZeroFlux zf(n);
            fp(" %s", Decimal(zf[i]).c_str() );
        }
        fp << "\n";
    }


}
Y_UDONE()
