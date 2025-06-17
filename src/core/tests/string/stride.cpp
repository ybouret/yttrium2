
#include "y/string/stride.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;

Y_UTEST(string_stride)
{

    Y_SIZEOF(Core::Stride<char>);
    Y_SIZEOF(Core::Stride<uint32_t>);


    AutoPtr< Core::Stride<char> > stride = new Core::Stride<char>(0);

}
Y_UDONE()

