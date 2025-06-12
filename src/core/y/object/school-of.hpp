
//! \file

#ifndef Y_Object_School_Of_Included
#define Y_Object_School_Of_Included

#include "y/object.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T>
        class SchoolOf
        {
        public:
            inline explicit SchoolOf(const size_t minimalCapacity) :
            count(minimalCapacity),
            bytes(0),
            entry( get() ),
            cxx(entry ? entry - 1 : 0)
            {
            }

            inline virtual ~SchoolOf() noexcept
            {
                if(0!=entry) {
                    static Allocator &mgr = Object::AllocatorLocation();
                    mgr.releaseAs<T>(Coerce(entry),Coerce(count),Coerce(bytes));
                    Coerce(cxx) = 0;
                }
            }

            const size_t count;
            const size_t bytes;
            T * const    entry;
            T * const    cxx;

        private:
            Y_Disable_Copy_And_Assign(SchoolOf);
            T * get() {
                static Allocator &mgr = Object::AllocatorInstance();
                return mgr.acquireAs<T>(Coerce(count), Coerce(bytes));
            }
        };
    }
}

#endif



