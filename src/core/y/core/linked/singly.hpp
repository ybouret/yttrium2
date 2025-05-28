//! \file

#ifndef Y_Core_Linked_Singly_Defined
#define Y_Core_Linked_Singly_Defined 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {

        //! helper to declare Singly Linked Type
        template <typename T>
        class SinglyLinked
        {
        public:
            //! setup
            inline explicit SinglyLinked() noexcept : next(0) {}

            //! cleanup
            inline virtual ~SinglyLinked() noexcept { assert(0==next); }

            T * next; //!< for pool
            
        private:
            Y_Disable_Copy_And_Assign(SinglyLinked); //!< discarding
        };
    }
}
#endif

