
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
            //! setup
            inline explicit DoublyLinked() noexcept : next(0), prev(0) {}

            //! cleanup
            inline virtual ~DoublyLinked() noexcept { assert(0==next); assert(0==prev); }

            T * next; //!< for list/pool
            T * prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(DoublyLinked); //!< discarding
        };
    }
}
#endif

