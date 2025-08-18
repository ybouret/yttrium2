#include "y/field/1d.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(field_1d)
{
    const Field::Format1D  fmt = new Field::Layout1D(-5,5);

    const Field::In1D<int> f1("f1",fmt);
    const Field::In1D<apq> fq("fq",fmt);

    std::cerr << f1 << std::endl;
    std::cerr << f1 << std::endl;

    Y_SIZEOF(Field::In1D<int>);
}
Y_UDONE()
