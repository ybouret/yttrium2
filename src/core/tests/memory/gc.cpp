
#include "y/ability/collectable.hpp"
#include "y/type/ints.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_gc)
{
    Y_CHECK( IntegerFor<size_t>::Maximum == Collectable::Portion(0xff,IntegerFor<size_t>::Maximum) );

    for(int i=1;i<argc;++i)
    {
        const size_t x = size_t(atol(argv[i]));
        for(unsigned j=0;j<256;++j)
        {
            const size_t y = Collectable::Portion( uint8_t(j), x );
            std::cerr << '(' << x << '*' << std::setw(3) << j << ')' << "/255 = " << y << std::endl;
        }
    }
}
Y_UDONE()
