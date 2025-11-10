
//! \file

#ifndef Y_Core_Linked_Info_Included
#define Y_Core_Linked_Info_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! common data for Linked structures
        //
        //______________________________________________________________________
        class LinkedInfo
        {

        public:
            static const char OwnsNode[]; //!< "owns node!"
            static const char NullNode[]; //!< "NULL==node"
            static const char UsedNext[]; //!< "NULL!=next"
            static const char UsedPrev[]; //!< "NULL!=prev"

            explicit LinkedInfo() noexcept; //!< setup
            virtual ~LinkedInfo() noexcept; //!< cleanup

            const size_t size; //!< number of nodes

        private:
            Y_Disable_Copy_And_Assign(LinkedInfo); //!< discard
        };
    }

}

#endif // !Y_Core_Linked_Info_Included

