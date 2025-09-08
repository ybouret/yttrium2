#include "y/utest/run.hpp"
#include "y/exception.hpp"

using namespace Yttrium;

Y_UTEST(exception)
{
    Y_SIZEOF(Exception);
    Y_SIZEOF(Specific::Exception);

    Specific::Exception excp("My Exception");

    excp.show(std::cerr);

}
Y_UDONE()

