

#include "y/jive/pattern/first-chars.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(fc)
{
    FirstChars lhs; lhs.add('a','p');
    std::cerr << lhs << std::endl;
    lhs.add('c','r');
    std::cerr << lhs << std::endl;
    FirstChars rhs; rhs.add('o','z');
    lhs += rhs;
    std::cerr << lhs << std::endl;

    rhs.free();
    rhs.add('g','v');
    lhs -= rhs;
    std::cerr << lhs << std::endl;


}
Y_UDONE()
