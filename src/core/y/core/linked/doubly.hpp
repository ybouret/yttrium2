
//! \file

#ifndef Y_Core_Linked_Doubly_Defined
#define Y_Core_Linked_Doubly_Defined 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {

        //! helper to declare Doubly Linked Type
        template <typename T>
        class DoublyLinked
        {
        public:
            inline explicit DoublyLinked() noexcept : next(0), prev(0) {}
            inline virtual ~DoublyLinked() noexcept { assert(0==next); assert(0==prev); }

            T * next;
            T * prev;
        private:
            Y_Disable_Copy_And_Assign(DoublyLinked);
        };
    }
}
#endif

