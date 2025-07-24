
//! \file

#ifndef Y_Object_School_Of_Included
#define Y_Object_School_Of_Included

#include "y/object.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! memory to hold a maximum count of objects
        //
        //
        //______________________________________________________________________
        template <typename T>
        class SchoolOf
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param minimalCapacity minimal value for count
            inline explicit SchoolOf(const size_t minimalCapacity) :
            maxBlocks(minimalCapacity),
            allocated(0),
            entry( get() ),
            cxx(entry ? entry - 1 : 0)
            {
            }

            //! release memory
            inline virtual ~SchoolOf() noexcept
            {
                if(0!=entry) {
                    static Allocator &mgr = Object::AllocatorLocation();
                    mgr.releaseAs<T>(Coerce(entry),Coerce(maxBlocks),Coerce(allocated));
                    Coerce(cxx) = 0;
                }
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            const size_t maxBlocks; //!< maximum numbers of objects to fit in
            const size_t allocated; //!< enough bytes to hold count objects
            T * const    entry;     //!< base address
            T * const    cxx;       //!< entry-1 for C++ access

        private:
            Y_Disable_Copy_And_Assign(SchoolOf); //!< discarding

            //! \return enough memory for count objects
            inline T * get() {
                static Allocator &mgr = Object::AllocatorInstance();
                return mgr.acquireAs<T>(Coerce(maxBlocks), Coerce(allocated));
            }
        };
    }
}

#endif



