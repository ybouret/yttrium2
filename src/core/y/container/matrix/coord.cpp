
#include "y/container/matrix/coord.hpp"
#include <iostream>

namespace Yttrium
{

    MatrixCoord:: ~MatrixCoord() noexcept
    {
        r=c=0;
    }

    MatrixCoord:: MatrixCoord(const size_t i, const size_t j) noexcept :
    r(i), c(j)
    {

    }

    MatrixCoord:: MatrixCoord(const MatrixCoord &_) noexcept :
    r(_.r),
    c(_.c)
    {
    }

    MatrixCoord & MatrixCoord:: operator=(const MatrixCoord &_) noexcept
    {
        r = _.r;
        c = _.c;
        return *this;
    }

    std::ostream & operator<<(std::ostream &os, const MatrixCoord &p)
    {
        os << '[' << p.r << ';' << p.c << ']';
        return os;
    }

}


