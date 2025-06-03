
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
                static const unsigned MinShift; //!< from object factor default page shift
                static const unsigned MaxShift = Segment::MaxDataShift;
                
                typedef Core::ListOf<Segment> ListType; //!< alias

                class Slot : public ListType
                {
                public:
                    explicit Slot() noexcept;
                    virtual ~Slot() noexcept;
                    void * reserved;

                private:
                    Y_Disable_Copy_And_Assign(Slot);
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
                uint32_t crc32() const noexcept;

            private:
                Y_Disable_Copy_And_Assign(Segments); //!< discarding

                void unload(Segment * const segment) noexcept;

                Slot * const           table;
                const Slot * const     lastSlot;
                const unsigned         tableShift;
                Object::Book         & book;
            };

        }

    }

}

#endif

