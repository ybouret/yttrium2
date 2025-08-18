
#include "y/field/2d.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(field_2d)
{

    const Field::Format2D  fmt = new Field::Layout2D( Field::Coord2D(-5,-6), Field::Coord2D(5,6) );
    const Field::In2D<int> f2("f2",fmt);
    const Field::In2D<apq> fq("fq",fmt);

    std::cerr << f2 << std::endl;
    std::cerr << fq << std::endl;

    Y_SIZEOF(Field::In2D<int>);

}
Y_UDONE()
