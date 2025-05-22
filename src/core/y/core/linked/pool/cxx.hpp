

//! \file

#ifndef Y_Core_Linked_Pool_Cxx_Included
#define Y_Core_Linked_Pool_Cxx_Included 1

#include "y/core/linked/pool.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //! list of nodes with copy constructor and C++ destructor
    template <typename NODE>
    class CxxPoolOf : public Core::PoolOf<NODE>, public Releasable
    {
    public:
        inline explicit CxxPoolOf() noexcept : Core::PoolOf<NODE>() {}
        inline virtual ~CxxPoolOf() noexcept { release_(); }
        inline CxxPoolOf(const CxxPoolOf &other) : Core::PoolOf<NODE>()
        {
            try
            {
                for(const NODE *node=other.head;node;node=node->next)
                    this->stash( new NODE(*node) );
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
        Y_Disable_Assign(CxxPoolOf);
        inline void release_() noexcept { while(this->size>0) delete this->popTail(); }
    };

}

#endif

