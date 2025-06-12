
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

        //______________________________________________________________________
        //
        //
        //
        //! Track Down memory location
        //
        //
        //______________________________________________________________________
        struct TrackDown
        {
            //! try to find which block
            /**
             \param blockAddr a used block address
             \param blockSize updated if found, 0 otherwise
             \return variety according to search
             */
            static Variety Which(const void * const blockAddr,
                                 size_t &           blockSize);

            //! human readable block findind
            /**
             \param os an output stream
             \param blockAddr a guess address
             \return os
             */
            static std::ostream & Print(std::ostream &os, const void * const blockAddr);
        };

    }
}

#endif

