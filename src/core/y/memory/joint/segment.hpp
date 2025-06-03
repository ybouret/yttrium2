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
                static const unsigned SegmentShift;                                //!< SegmentBytes = 2^SegmentShift
                static const size_t   MinNumBlocks = 3;                            //!< head+free block+tail
                static const size_t   MinDataBytes;                                //!< SegmentBytes + MinNumBlocks * BlockSize
                static const unsigned MinDataShift;
                static const unsigned MaxDataShift = Base2<size_t>::MaxShift;
                struct Param
                {
                    unsigned shift;
                    size_t   bytes;
                };


                //! format a segment
                /**
                 \param entry valid dyadic memory
                 \param shift shift >= MinDataShift, shift  <= Base2::MaxShift
                 \return a formatted segment
                 */
                static Segment * Format(void * const   entry,
                                        const unsigned shift);

                //! Display, mostly for debug
                void display(std::ostream &) const;

                //! check validity, mostly for debug \return true iff valid
                static bool      IsValid(const Segment * const) noexcept;

                //! try to acquire a new block with blockSize>=request
                /**
                 \param request minimal bytes to get, updated upon success
                 \return 0 if not found and request is untouched, address and request otherwise
                 */
                void * acquire(size_t & request) noexcept;

                //! CRC32 of markers
                /**
                 \param segment a valid segment
                 \return crc of all blocks
                 */
                static uint32_t CRC(const Segment * segment) noexcept;

                //! (fast) check of ownership
                /**
                 \return true iff address between head an tail
                 */
                static bool      Owns(const Segment * const, void * const) noexcept;

                //! check empty \return true iff unused head whose next is tail
                static bool      IsEmpy(const Segment *const) noexcept;

                
                //! releasing and address
                /**
                 \param addr previousluy acquired
                 \return owning segment
                 */
                static Segment * Release(void * const addr)   noexcept;

                static size_t BytesFor(const size_t blockSize);

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
                union {
                    Block bogus;
                    Param param;
                };

            };
        }
    }
}


#endif

