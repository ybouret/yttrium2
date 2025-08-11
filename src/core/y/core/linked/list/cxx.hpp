
//! \file

#ifndef Y_Core_Linked_List_Cxx_Included
#define Y_Core_Linked_List_Cxx_Included 1

#include "y/core/linked/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! list of nodes with copy constructor and C++ destructor
    //
    //
    //__________________________________________________________________________
    template <typename NODE>
    class CxxListOf : public Core::ListOf<NODE>, public Releasable
    {
    public:

        //! initialize
        inline explicit CxxListOf() noexcept :
        Core::ListOf<NODE>(),
        Releasable()
        {
        }

        //! cleanup
        inline virtual ~CxxListOf() noexcept { release_(); }

        //! duplicate
        /** \param other another list */
        inline CxxListOf(const CxxListOf &other) :
        Core::ListOf<NODE>(),
        Releasable()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->pushTail( new NODE(*node) );
                assert(this->size==other.size);
            }
            catch(...)
            {
                release_();
                throw;
            }
        }

        //! delete all nodes
        inline virtual void release() noexcept {
            release_();
        }

    private:
        Y_Disable_Assign(CxxListOf); //!< discarding

        //! delete all nodes
        inline void release_() noexcept { while(this->size>0) delete this->popTail(); }
    };

}

#endif

