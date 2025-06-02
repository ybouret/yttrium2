//! \file

#ifndef Y_Memory_Joint_Segment_Included
#define Y_Memory_Joint_Segment_Included 1

#include "y/core/setup.hpp"
#include "y/type/ints.hpp"

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

                Segment *next;
                Segment *prev;

                static Segment * Format(void * const  entry,
                                        const  size_t bytes);

            };
        }
    }
}


#endif

