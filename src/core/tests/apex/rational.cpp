

#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(apex_q)
{

    { const apq q; std::cerr << q << std::endl; }

    { const apq q(-3,9); std::cerr << q << std::endl; }


}
Y_UDONE()

