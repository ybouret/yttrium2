#include "y/concurrent/api/loop/crew.hpp"
#include "y/concurrent/api/loop/sole.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_loop)
{
    Concurrent::Loop::Verbose = Environment::Flag("VERBOSE");
    size_t n = 1;
    if(argc>1) n = ASCII::Convert::To<size_t>(argv[1],"n");

    Concurrent::Crew crew(n);


}
Y_UDONE()

