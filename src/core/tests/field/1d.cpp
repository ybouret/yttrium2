#include "y/field/1d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(field_1d)
{
    const Field::Format1D  fmt = new Field::Layout1D(-5,5);
    const Field::In1D<int> f1("f1",fmt);
}
Y_UDONE()
