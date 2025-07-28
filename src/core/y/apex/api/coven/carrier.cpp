
#include "y/apex/api/coven/carrier.hpp"

namespace Yttrium
{

    namespace Coven
    {


        Carrier:: ~Carrier() noexcept
        {
        }


        Carrier:: Carrier(const size_t dims) :
        QMetrics(dims),
        vpool(*this),
        fpool(vpool)
        {
        }

    }

}
