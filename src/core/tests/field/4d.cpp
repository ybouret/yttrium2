


#include "y/field/4d.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;

Y_UTEST(field_4d)
{
    const Field::Format4D  fmt = new Field::Layout4D( Field::Coord4D(-2,-3,-4,-5), Field::Coord4D(2,3,4,5) );
    std::cerr << "fmt=" << fmt << std::endl;
    Field::In4D<int> f4("f4",fmt);
    Field::In4D<apq> fq("fq",fmt);
    std::cerr << fq << std::endl;
    


}
Y_UDONE()
