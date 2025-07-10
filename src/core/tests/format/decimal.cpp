
#include "y/format/decimal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(format_decimal)
{

    for(int i=1;i<argc;++i)
    {
        const long x = atol(argv[i]);
        std::cerr << x << "->" << Decimal(x) << std::endl;
    }

}
Y_UDONE()
