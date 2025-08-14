
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
                    { const Segment<T> segm(offset,todo,todo>0? (offset+todo)-1 : offset); segments << segm; }
                    offset += todo;
                    length -= todo;
                }
            }

        }

    }
}

#endif

