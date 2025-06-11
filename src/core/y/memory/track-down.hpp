
//! \file

#ifndef Y_Memory_Track_Down_Included
#define Y_Memory_Track_Down_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //! Memory Variety
        //
        //______________________________________________________________________
        enum Variety
        {
            SmallType, //!< in Small::Blocks
            JointType, //!< in Pooled allocator
            OtherType  //!< larger than previous
        };

        struct TrackDown
        {
            //! Track down memory location
            /**
             \param blockAddr a used block address
             \param blockSize updated if found, 0 otherwise
             \return variety according to search
             */
            static Variety Block(const void * const blockAddr,
                                        size_t &           blockSize);

            static std::ostream & Print(std::ostream &os, const void * const blockAddr);
        };

    }
}

#endif

