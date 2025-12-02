#include "y/concurrent/split/1d.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            Zone:: Zone() noexcept : offset(0), length(0)
            {
            }

            Zone:: ~Zone() noexcept
            {
            }

            Zone:: Zone(const Zone &zone) noexcept :
            offset(zone.offset),
            length(zone.length)
            {
            }

            std::ostream & operator<< (std::ostream &os, const Zone &zone)
            {
                os << "@" << zone.offset << "[" << zone.length << "]";
                return os;
            }

        }

        namespace Split
        {

            In1D:: ~In1D() noexcept
            {
            }

            In1D:: In1D(const uint64_t count) noexcept :
            divide(0),
            remain(0),
            burden(count)
            {
            }

            void In1D:: boot(const size_t   numProcessors,
                             const uint64_t initialOffset) noexcept
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


            Zone In1D:: operator()(const Member &m, const uint64_t initialOffset) noexcept
            {
                boot(m.size,initialOffset);
                for(size_t i=m.indx;i>0;--i) (void) next();
                return *this;
            }


        }

    }
}


