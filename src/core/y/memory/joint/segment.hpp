//! \file

#ifndef Y_Memory_Joint_Segment_Included
#define Y_Memory_Joint_Segment_Included 1

#include "y/calculus/base2.hpp"
#include "y/type/ints.hpp"
#include "y/memory/page.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Joint
        {



            struct Segment
            {
                static const char * const CallSign;
                typedef UnsignedIntFor<void*>::Result::Type len_t;
                struct Block
                {
                    Segment * link;
                    len_t     size;
                    Block   * next;
                    Block   * prev;
                };
                static const size_t   BlockSize    = sizeof(Block);
                static const unsigned BlockLog2    = IntegerLog2For<Block>::Value;
                static const size_t   SegmentBytes;
                static const size_t   MinNumBlocks = 3;
                static const size_t   MinDataBytes;

                Segment *     next;
                Segment *     prev;
                Block * const head;
                Block * const tail;

                static Segment * Format(void * const  entry,
                                        const  size_t bytes);

                static void      Display(const Segment * const,std::ostream &);

            };
        }
    }
}


#endif

