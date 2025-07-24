

#include "y/hashing/perfect.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"
#include "y/stream/libc/input.hpp"

using namespace Yttrium;

Y_UTEST(hashing_perfect)
{
    const char msg[] = "Hello World!";

    Hashing::Perfect mph;

    int k = 0;

    mph(msg,++k);

}
Y_UDONE()

