

//! \file

#ifndef Y_Core_Linked_Pool_Cxx_Included
#define Y_Core_Linked_Pool_Cxx_Included 1

#include "y/core/linked/pool.hpp"
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
    class CxxPoolOf : public Core::PoolOf<NODE>, public Releasable
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! initialize
        inline explicit CxxPoolOf() noexcept : Core::PoolOf<NODE>() {}

        //! cleanup
        inline virtual ~CxxPoolOf() noexcept { release_(); }

        //! duplicate using node copy semantics
        /** \param *other other pool */
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

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        inline virtual void release() noexcept {
            release_();
        }

    private:
        Y_Disable_Assign(CxxPoolOf); //!< discarding

        //! release all nodes
        inline void release_() noexcept { while(this->size>0) delete this->query(); }
    };

}

#endif

