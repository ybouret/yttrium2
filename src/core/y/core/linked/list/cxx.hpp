
//! \file

#ifndef Y_Core_Linked_List_Cxx_Included
#define Y_Core_Linked_List_Cxx_Included 1

#include "y/core/linked/list.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //! list of nodes with copy constructor and C++ destructor
    template <typename NODE>
    class CxxListOf : public Core::ListOf<NODE>, public Releasable
    {
    public:
        inline explicit CxxListOf() noexcept : Core::ListOf<NODE>() {}
        inline virtual ~CxxListOf() noexcept { release_(); }
        inline CxxListOf(const CxxListOf &other) : Core::ListOf<NODE>()
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

        inline virtual void release() noexcept {
            release_();
        }

    private:
        Y_Disable_Assign(CxxListOf);
        inline void release_() noexcept { while(this->size>0) delete this->popTail(); }
    };

}

#endif

