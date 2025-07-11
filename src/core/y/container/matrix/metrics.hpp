
//! \file

#ifndef Y_Matrix_Metrics_Included
#define Y_Matrix_Metrics_Included 1

#include "y/mkl/transpose-of.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{


    class MatrixMetrics
    {
    public:
        static const char * const CallSign; //!< matrix
        static const char * const EmptyMatrix;

        explicit MatrixMetrics(const size_t nr, const size_t nc);
        MatrixMetrics(const MatrixMetrics &) noexcept; //!< duplicate
        MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &) noexcept;
        virtual ~MatrixMetrics() noexcept;             //!< cleanup

        const size_t rows;
        const size_t cols;
        const size_t count;

    private:
        Y_Disable_Assign(MatrixMetrics);
    };

}

#endif
