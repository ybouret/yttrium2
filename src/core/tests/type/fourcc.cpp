#include "y/type/fourcc.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(type_fourcc)
{
    std::cerr << FourCC(0x12345678) << std::endl;
    std::cerr << FourCC( Y_FOURCC('a', 'b', 'c', 'd') ) << std::endl;
    std::cerr << FourCC(0xffffffff) << std::endl;
}
Y_UDONE()
