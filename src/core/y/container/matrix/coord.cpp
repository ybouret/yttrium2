
#include "y/container/matrix/coord.hpp"

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


}


