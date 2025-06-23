

#include "y/string.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace Yttrium
{

    
}

Y_UTEST(string)
{

    { String s; std::cerr << s << std::endl; }
    { String s = "a"; std::cerr << s << std::endl; }
    { String s = 'a'; std::cerr << s << std::endl; }
    {
        String s = "first";
        s += " second";
        std::cerr << s << std::endl;
    }
    
}
Y_UDONE()

