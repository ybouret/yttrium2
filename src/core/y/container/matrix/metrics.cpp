
#include "y/container/matrix/metrics.hpp"
#include "y/system/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    MatrixMetrics:: ~MatrixMetrics() noexcept
    {

    }

    const char * const MatrixMetrics:: CallSign = "Matrix";

    MatrixMetrics:: MatrixMetrics(const size_t nr,
                                  const size_t nc) :
    rows(nr),
    cols(nr),
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


}


