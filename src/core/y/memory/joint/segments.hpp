
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
        namespace Object
        {
            class Book;
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
                //! slot for table: list of ordered segments
                //
                //______________________________________________________________
                class Slot : public ListType
                {
                public:
                    explicit Slot() noexcept; //!< setup
                    virtual ~Slot() noexcept; //!< cleanup
                    Segment * alreadyEmpty;   //!< bookkeeping

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
                void *   acquire(size_t &blockSize);
                void     release(void * const blockAddr) noexcept;
                uint32_t crc32() const noexcept; //!< full crc \return crc of chained segments

            private:
                Y_Disable_Copy_And_Assign(Segments); //!< discarding

                //! return segment to book
                void unload(Segment * const) noexcept;

                Slot * const           table;      //!< table of list of segments
                const Slot * const     lastSlot;   //!< first invalid slot address
                const unsigned         tableShift; //!< memory shift to hild table
                Object::Book         & book;       //!< memory cache for segments
            };

        }

    }

}

#endif

