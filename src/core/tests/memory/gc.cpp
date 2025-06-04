
#include "y/ability/collectable.hpp"
#include "y/type/ints.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_gc)
{
    Collectable::Mul(0xff,IntegerFor<size_t>::Maximum);
}
Y_UDONE()
