

#include "y/static/replica.hpp"
#include "y/utest/run.hpp"
#include "y/apex/natural.hpp"

using namespace Yttrium;


Y_UTEST(static_replica)
{

    apn n = 10;
    Static::Replica<apn> D(n);
    std::cerr << D << std::endl;
    D.free();
    std::cerr << D << std::endl;
    n = 12;
    D = n;
    std::cerr << D << std::endl;

}
Y_UDONE()
