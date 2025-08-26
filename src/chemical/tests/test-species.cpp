
#include "y/chemical/species.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(species)
{
    for(int i=1;i<argc;++i)
    {
        const Species sp(argv[i],1);
        std::cerr << sp << std::endl;
    }

}
Y_UDONE()
