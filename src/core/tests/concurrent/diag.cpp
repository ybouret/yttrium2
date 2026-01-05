

#include "y/concurrent/divide/udt.hpp"
#include "y/utest/run.hpp"
#include "y/string/env/convert.hpp"


using namespace Yttrium;




Y_UTEST(concurrent_diag)
{

    const size_t n = EnvironmentConvert::To<size_t>("n",10);

    Concurrent::Divide::UpperDiagonalTile udt(1,1,n);



}
Y_UDONE()
