#include "y/concurrent/api/loop/crew.hpp"
#include "y/concurrent/api/loop/sole.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_loop)
{

    size_t n = 1;
    if(argc>1) n = ASCII::Convert::To<size_t>(argv[1],"n");
    Concurrent::Crew crew(n);
    

}
Y_UDONE()

