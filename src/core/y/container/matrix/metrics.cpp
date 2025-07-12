
#include "y/container/matrix/metrics.hpp"
#include "y/system/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    MatrixMetrics:: ~MatrixMetrics() noexcept
    {

    }

    const char * const MatrixMetrics:: CallSign    = "Matrix";
    const char * const MatrixMetrics:: EmptyMatrix = "[]";
    const char * const MatrixMetrics:: L_HCAT      = "hcat(";
    const char * const MatrixMetrics:: R_HCAT      = ")";

    MatrixMetrics:: MatrixMetrics(const size_t nr,
                                  const size_t nc) :
    rows(nr),
    cols(nc),
    count(rows*cols)
    {
        if( (nr<=0 && nc>0) || (nr>0&&nc<=0) )
            throw Specific::Exception(CallSign,"invalid %s x %s", Decimal(rows).c_str(), Decimal(cols).c_str() );
    }

    MatrixMetrics:: MatrixMetrics(const MatrixMetrics &_) noexcept :
    rows(_.rows),
    cols(_.cols),
    count(_.count)
    {
    }

    MatrixMetrics:: MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &_) noexcept :
    rows(_.cols),
    cols(_.rows),
    count(_.count)
    {
    }

    bool MatrixMetrics:: isSquare() const noexcept
    {
        return cols == rows;
    }

    bool MatrixMetrics:: sameMetricsThan(const MatrixMetrics &M) const noexcept
    {
        return rows == M.rows && cols == M.cols;
    }

    void MatrixMetrics:: _xch( MatrixMetrics &m ) noexcept
    {
        CoerceSwap(rows,m.rows);
        CoerceSwap(cols,m.cols);
        CoerceSwap(count,m.count);
    }


    size_t MatrixMetrics:: indexOf(const size_t ir, const size_t ic) const noexcept
    {
        assert(ir>=0);
        assert(ir<rows);
        assert(ic>=0);
        assert(ic<cols);
        return ir * rows + ic;
    }



}


