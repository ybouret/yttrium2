
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(fmt)
{
    Ink::Formats &IMG = Ink::Formats::Std();
    IMG.display(std::cerr,0);
    
}
Y_UDONE()
