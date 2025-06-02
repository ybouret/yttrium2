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


            //__________________________________________________________________
            //
            //
            //
            //! standalone Segment on a memory workspace
            //
            //
            //__________________________________________________________________
            struct Segment
            {
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Segment(); //!< disable constructor

                static const char * const CallSign;                 //!< "Memory::Joint::Segment"
                typedef UnsignedIntFor<void*>::Result::Type len_t; //!< alias

                //! internal block marker
                struct Block
                {
                    Segment * used; //!< 0==free, otherwise owner Segment
                    len_t     size; //!< available bytes
                    Block   * next; //!< for internal list
                    Block   * prev; //!< for internal list
                };

                static const size_t   BlockSize     = sizeof(Block);               //!< allocation granularity
                static const unsigned BlockLog2    = IntegerLog2For<Block>::Value; //!< ensure power of two
                static const size_t   SegmentBytes;                                //!< sizeof(SegmentBytes)
                static const size_t   MinNumBlocks = 3;                            //!< head+free block+tail
                static const size_t   MinDataBytes;                                //!< SegmentBytes + MinNumBlocks * BlockSize



                //! format a segment
                /**
                 \param entry valid memory
                 \param bytes bytes >= MinDataBytes
                 \return a formatted segment
                 */
                static Segment * Format(void * const entry, const size_t bytes);

                //! Display, mostly for debug
                static void      Display(const Segment * const,std::ostream &);

                //! check validity, mostly for debug \return true iff valid
                static bool      IsValid(const Segment * const) noexcept;

                //! try to acquire a new block with blockSize>=request
                /**
                 \param segment formatted segment
                 \param request minimal bytes to get, updated upon success
                 \return 0 if not found and request is untouched, address and request otherwise
                 */
                static void *    Acquire(Segment * const segment,
                                         size_t &        request) noexcept;

                //! CRC32 of markers
                static uint32_t CRC(const Segment * segment) noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Segment *     next; //!< for list/cache
                Segment *     prev; //!< for list/cache
                Block * const head; //!< head marker
                Block * const tail; //!< tail marker

            };
        }
    }
}


#endif

