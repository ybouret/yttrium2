#include "y/field/layout/1d.hpp"
#include "y/field/layout/2d.hpp"
#include "y/field/layout/3d.hpp"
#include "y/field/layout/4d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Field;

Y_UTEST(field_layout)
{


    {
        std::cerr << std::endl << "1D" << std::endl;
        Format1D fmt = new  Layout1D(-5,5);
        std::cerr << fmt << std::endl;
    }

    {
        std::cerr << std::endl << "2D" << std::endl;
        Format2D fmt = new  Layout2D(Coord2D(-1,-2),Coord2D(4,3));
        std::cerr << "f2=" << fmt << std::endl;
        Format1D f1 = new Layout1D(SubLayout,*fmt);
        std::cerr << "f1=" << f1 << std::endl;

    }

    {
        std::cerr << std::endl << "3D" << std::endl;
        Format3D fmt = new  Layout3D(Coord3D(-3,-2,-1),Coord3D(6,5,4));
        std::cerr << "f3=" << fmt << std::endl;
        Format2D f2 = new  Layout2D(SubLayout,*fmt);
        Format1D f1 = new  Layout1D(SubLayout,*f2);
        std::cerr << "f2=" << f2 << std::endl;
        std::cerr << "f1=" << f1 << std::endl;
    }


    {
        std::cerr << std::endl << "4D" << std::endl;
        Format4D fmt = new  Layout4D(Coord4D(-4,-3,-2,-1),Coord4D(4,5,6,7));
        std::cerr << "f4=" << fmt << std::endl;

        Format3D f3 = new  Layout3D(SubLayout,*fmt);
        Format2D f2 = new  Layout2D(SubLayout,*f3);
        Format1D f1 = new  Layout1D(SubLayout,*f2);

        std::cerr << "f3=" << f3 << std::endl;
        std::cerr << "f2=" << f2 << std::endl;
        std::cerr << "f1=" << f1 << std::endl;
    }


}
Y_UDONE()
