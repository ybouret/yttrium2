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
            origin(count)
            {
            }

            void In1D:: boot(const size_t nproc) noexcept
            {
                assert(nproc>0);
                divide = nproc;
                remain = origin;
                Coerce(offset) = 1;
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


