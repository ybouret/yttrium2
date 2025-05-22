

//! \file

#ifndef Y_Core_Linked_List_Cloneable_Included
#define Y_Core_Linked_List_Cloneable_Included 1

#include "y/core/linked/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //! list of nodes with clone method and C++ destructor
    template <typename NODE>
    class ListOfCloneable : public Core::ListOf<NODE>, public Releasable
    {
    public:
        inline explicit ListOfCloneable() noexcept :
        Core::ListOf<NODE>(),
        Releasable()
        {}

        inline virtual ~ListOfCloneable() noexcept { release_(); }

        inline ListOfCloneable(const ListOfCloneable &other) :
        Core::ListOf<NODE>(), Releasable()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->pushTail( node->clone()  );
                assert(this->size==other.size);
            }
            catch(...)
            {
                release_();
                throw;
            }
        }

        inline virtual void release() noexcept {
            release_();
        }

    private:
        Y_Disable_Assign(ListOfCloneable);
        inline void release_() noexcept { while(this->size>0) delete this->popTail(); }
    };

}

#endif

