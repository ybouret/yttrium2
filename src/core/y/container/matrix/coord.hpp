

//! \file

#ifndef Y_Matrix_Coord_Included
#define Y_Matrix_Coord_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    class MatrixCoord
    {
    public:
        MatrixCoord(const size_t i, const size_t j)  noexcept; //!<
        ~MatrixCoord()                               noexcept; //!<
        MatrixCoord(const MatrixCoord &)             noexcept; //!<
        MatrixCoord & operator=(const MatrixCoord &) noexcept; //!<

        size_t r; //!< row index
        size_t c; //!< column index
    };
}

#endif // !Y_Matrix_Coord_Included

