
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
        class Dyadic;

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
                typedef Core::ListOf<Segment> ListType; //!< alias

                class Slot : public ListType
                {
                public:
                    explicit Slot() noexcept;
                    virtual ~Slot() noexcept;
                    
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
                void * acquire(size_t &blockSize);
                void   release(void * const blockAddr) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Segments); //!< discarding

                void unload(Segment * const segment) noexcept;

                Slot * const           table;
                const unsigned         tableShift;
                Dyadic               & dyadic;

            };

        }

    }

}

#endif

