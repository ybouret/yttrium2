

#include "y/jive/pattern/first-chars.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(fc)
{

    {
        FirstChars fc;
        fc.add('a');
        std::cerr << fc << std::endl;
        fc.add('c');
        std::cerr << fc << std::endl;
        fc.add('b');
        std::cerr << fc << std::endl;
        fc.all();
        std::cerr << fc << std::endl;
        fc.sub('a');
        std::cerr << fc << std::endl;
        fc.sub('0');
        std::cerr << fc << std::endl;

    }

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

}
Y_UDONE()
