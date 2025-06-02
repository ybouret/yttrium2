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
                Segment();

                static const char * const CallSign;
                typedef UnsignedIntFor<void*>::Result::Type len_t;
                struct Block
                {
                    Segment * used;
                    len_t     size;
                    Block   * next;
                    Block   * prev;
                };
                static const size_t   BlockSize    = sizeof(Block); //!< allocation granularity
                static const unsigned BlockLog2    = IntegerLog2For<Block>::Value; //!< ensure power of two
                static const size_t   SegmentBytes;      //!< sizeof(SegmentBytes)
                static const size_t   MinNumBlocks = 3;  //!< head+free block+tail
                static const size_t   MinDataBytes;      //!< SegmentBytes + MinNumBlocks * BlockSize

                Segment *     next;
                Segment *     prev;
                Block * const head;
                Block * const tail;

                static Segment * Format(void * const  entry,
                                        const  size_t bytes);
                static void      Display(const Segment * const,std::ostream &);
                static bool      IsValid(const Segment * const) noexcept;

                //!
                /**
                 \return 0 if not found and request is untouched, address and request otherwise
                 */
                static void *    Acquire(Segment * const segment,
                                         size_t &        request) noexcept;

            };
        }
    }
}


#endif

