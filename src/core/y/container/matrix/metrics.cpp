
#include "y/container/matrix/metrics.hpp"
#include "y/exception.hpp"
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


    static inline bool badMetrics(const size_t nr, const size_t nc)
    {
        return (nr<=0 && nc>0) || (nr>0&&nc<=0);
    }

    MatrixMetrics:: MatrixMetrics(const size_t nr,
                                  const size_t nc) :
    rows(nr),
    cols(nc),
    items(rows*cols)
    {
        if( badMetrics(nr,nc) )
            throw Specific::Exception(CallSign,"invalid %s x %s", Decimal(rows).c_str(), Decimal(cols).c_str() );
    }

    MatrixMetrics:: MatrixMetrics(const MatrixMetrics &_) noexcept :
    rows(_.rows),
    cols(_.cols),
    items(_.items)
    {
    }

    static inline size_t minorRows(const MatrixMetrics &_)
    {
        const size_t nr = _.rows;
        if(nr<=0) throw Specific::Exception(_.CallSign,"not enough rows for minor");
        return nr-1;
    }

    static inline size_t minorCols(const MatrixMetrics &_)
    {
        const size_t nc = _.cols;
        if(nc<=0) throw Specific::Exception(_.CallSign,"not enough colums for minor");
        return nc-1;
    }


    MatrixMetrics:: MatrixMetrics(const MinorOf_ &, const MatrixMetrics &_) :
    rows( minorRows(_) ),
    cols( minorCols(_) ),
    items(rows*cols)
    {
        if( badMetrics(rows,cols) ) throw Specific::Exception(_.CallSign,"invalid metrics for minor");
    }


    MatrixMetrics:: MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &_) noexcept :
    rows(_.cols),
    cols(_.rows),
    items(_.items)
    {
    }

    bool MatrixMetrics:: isSquare() const noexcept
    {
        return cols == rows;
    }

    bool MatrixMetrics:: gotSameMetricsThan(const MatrixMetrics &M) const noexcept
    {
        return rows == M.rows && cols == M.cols;
    }

    bool MatrixMetrics:: transposeMetricsOf(const MatrixMetrics &M) const noexcept
    {
        return rows == M.cols && cols == M.rows;
    }


    void MatrixMetrics:: _xch( MatrixMetrics &m ) noexcept
    {
        CoerceSwap(rows,m.rows);
        CoerceSwap(cols,m.cols);
        CoerceSwap(items,m.items);
    }


    



}


