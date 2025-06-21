
#include "y/string/stride.hpp"
#include "y/utest/run.hpp"
#include "y/pointer/auto.hpp"
#include "y/memory/track-down.hpp"

using namespace Yttrium;


Y_UTEST(string_stride)
{

    Y_SIZEOF(Core::Stride<char>);
    Y_SIZEOF(Core::Stride<uint32_t>);


    AutoPtr< Core::Stride<char> >     stride8  = new Core::Stride<char>(0);
    AutoPtr< Core::Stride<uint32_t> > stride32 = new Core::Stride<uint32_t>(10);

}
Y_UDONE()

