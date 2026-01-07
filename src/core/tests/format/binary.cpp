

#include "y/format/binary.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(format_binary)
{

    for(int i=1;i<argc;++i)
    {
        const long x = atol(argv[i]);
        std::cerr << x << "->" << Binary(x) << std::endl;
    }

}
Y_UDONE()
