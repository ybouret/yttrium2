
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/format/decimal.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {
            template <typename T>
            class Segment
            {
            public:
                const T      offset;
                const size_t length;
                const T      latest;

                inline Segment(const T first, const size_t count) noexcept :
                offset(first),
                length(count),
                latest( length > 0 ? (offset+length)-1 : offset)
                {
                }

                inline ~Segment() noexcept {}

                Segment(const Segment &s) noexcept :
                offset(s.offset),
                length(s.length),
                latest(s.latest)
                {
                }

                inline friend std::ostream & operator<<(std::ostream &os, const Segment &self)
                {
                    return os << '#' << '[' << Decimal(self.offset) << ':' << Decimal(self.latest) << ']' << '=' << Decimal(self.length);
                }


            private:
                Y_Disable_Assign(Segment);
            };


            template <typename SEQUENCE,typename T>
            inline void In1D(SEQUENCE    &segments,
                             const T      first,
                             const size_t count,
                             const size_t nproc)
            {
                assert(nproc>0);
                segments.free();
                T      offset = first;
                size_t length = count;
                for(size_t num=1,den=nproc;num<=nproc;++num,--den)
                {
                    const size_t todo = length/den;
                    { const Segment<T> segm(offset,todo); segments << segm; }
                    offset += todo;
                    length -= todo;
                }
            }

        }

    }
}

#endif

