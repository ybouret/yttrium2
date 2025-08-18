

#include "y/field/3d.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(field_3d)
{

    const Field::Format3D  fmt = new Field::Layout3D( Field::Coord3D(-5,-6,-7), Field::Coord3D(5,6,7) );

    std::cerr << "fmt=" << fmt << std::endl;

    Field::In3D<int> f3("f3",fmt);
    Field::In3D<apq> fq("fq",fmt);

    std::cerr << fq << std::endl;

    

}
Y_UDONE()
