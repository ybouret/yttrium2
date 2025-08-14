
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/concurrent/split/segment.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //! split 1D count in nproc segments
            /**
             \param segments compatible sequence of segements
             \param first    first offset
             \param count    items to split
             \param nproc    nproc>0 
             */
            template <typename SEQUENCE,typename T>
            inline void In1D_(SEQUENCE    &segments,
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
                    { const Segment<T> segm(offset,todo,todo>0? (offset+todo)-1 : offset); segments << segm; }
                    offset += todo;
                    length -= todo;
                }
            }

            template <typename T>
            class In1D : public Segment<T>
            {
            public:
                typedef Segment<T> SegmentType;
                using SegmentType::offset;
                using SegmentType::length;

                inline In1D(const T first, const size_t count) noexcept :
                SegmentType(0,0),
                den(0),
                off(0),
                rem(0),
                full(first,count)
                {

                }

                inline virtual ~In1D() noexcept {}

                void boot(const size_t nproc) noexcept
                {
                    assert(nproc>0);
                    off = full.offset;
                    rem = full.length;
                    den = nproc;
                }

                bool next() noexcept
                {
                    if(den<=0) return false;
                    const size_t len = rem/den--;
                    Coerce(offset) = off;
                    Coerce(length) = len;
                    off += len;
                    rem -= len;
                    return true;
                }


            private:
                size_t            den;
                T                 off;
                size_t            rem;
            public:
                const SegmentType full;
            private:
                Y_Disable_Copy_And_Assign(In1D);
            };

        }

    }
}

#endif

