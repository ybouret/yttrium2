
//! \file

#ifndef Y_Memory_Joint_Segments_Included
#define Y_Memory_Joint_Segments_Included 1

#include "y/core/setup.hpp"
#include "y/core/linked/list.hpp"
#include "y/memory/joint/segment.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {
            class Ledger;
        }

        namespace Joint
        {

            //__________________________________________________________________
            //
            //
            //
            //! Segments on dyadic allocator
            //
            //
            //__________________________________________________________________
            class Segments
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unsigned MinShift;                         //!< from object factor default page shift
                static const unsigned MaxShift = Segment::MaxDataShift; //!< alias
                typedef Core::ListOf<Segment> ListType; //!< alias

                //______________________________________________________________
                //
                //
                //! slot for table: list of segments (odered by memory)
                //
                //______________________________________________________________
                class Slot : public ListType
                {
                public:
                    explicit Slot() noexcept; //!< setup
                    virtual ~Slot() noexcept; //!< cleanup
                    Segment * alreadyEmpty;   //!< bookkeeping

                    //! show raws of memory structure snapshot
                    void show(std::ostream &,size_t) const;

                private:
                    Y_Disable_Copy_And_Assign(Slot); //!< discarding
                };


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Segments();          //!< initialize
                virtual ~Segments() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! acquire a new memory block
                /**
                 - look into acceptable slots
                 - create the tighest one if not possible
                 - take care of slot.alreadyEmpty
                 \param  blockSize block size
                 \return a new memory with updated blockSize
                 */
                void *   acquire(size_t &blockSize);

                //! release an old memory block
                /**
                 - find the owner's
                 - check no multiple alreadyEmpty in matching slot
                 \param blockAddr address of acquired block
                 \param blockSize its size for consistency
                 */
                void     release(void * const blockAddr,
                                 const size_t blockSize) noexcept;

                uint32_t crc32() const noexcept; //!< full crc \return crc of chained segments

                //! access slot by its shift
                /**
                 \param shift a valid shift
                 \return a valid slot
                 */
                const Slot & operator[](const unsigned shift) const noexcept;

                //! look for memory
                /**
                 \param blockAddr address of block
                 \param blockSize updated block size if found
                 \return true if found in handled memory
                 */
                bool owns(const void * const blockAddr,
                          size_t &           blockSize) const noexcept;

            private:
                Y_Disable_Copy_And_Assign(Segments); //!< discarding

                //! return segment to book
                void unload(Segment * const) noexcept;

                Slot * const           table;      //!< table of list of segments
                const Slot * const     lastSlot;   //!< first invalid slot address
                const unsigned         tableShift; //!< memory shift to hild table
                Small::Ledger        & ledger;     //!< memory cache for segments
            };

        }

    }

}

#endif

