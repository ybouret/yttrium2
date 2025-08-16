#include "y/concurrent/split/1d.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            In1D:: ~In1D() noexcept
            {
            }

            In1D:: In1D(const size_t count) noexcept :
            offset(0),
            length(0),
            divide(0),
            remain(0),
            burden(count)
            {
            }

            void In1D:: boot(const size_t numProcessors,
                             const size_t initialOffset) noexcept
            {
                assert(numProcessors>0);
                divide = numProcessors;
                remain = burden;
                Coerce(offset) = initialOffset;
                Coerce(length) = 0;
            }

            bool In1D:: next() noexcept
            {
                if(divide<=0) return false;
                Coerce(offset) += length;
                Coerce(length)  = remain/divide--;
                remain -= length;
                return true;
            }

        }

    }
}


