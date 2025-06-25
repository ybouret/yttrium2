
#include "y/apex/metrics.hpp"
#include "y/calculus/alignment.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        void Metrics:: Overflow(const size_t bytes)
        {
            throw Libc::Exception(EDOM,"Apex::Metrics::Overflow(%s)", Decimal(bytes).c_str());
        }

        size_t Metrics:: BytesFor(size_t bytes, unsigned &shift)
        { 
            if(bytes>MaxBytes) Overflow(bytes);
            if(bytes<MinBytes) bytes = MinBytes;
            return NextPowerOfTwo(bytes,shift);
        }
    }
}
