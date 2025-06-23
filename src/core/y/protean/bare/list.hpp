
//! \file

#ifndef Y_Protean_BareList_Included
#define Y_Protean_BareList_Included 1

#include "y/protean/proto/list.hpp"
#include "y/protean/cache/direct.hpp"
#include "y/container.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! Bare List interface
        //
        //
        //______________________________________________________________________
        template <
        typename NODE,
        typename ThreadingPolicy>
        class BareList :
        public ListProto<NODE,DirectCacheOf<NODE>,Container,ThreadingPolicy>,
        public Releasable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef DirectCacheOf<NODE>                                PoolType; //!< alias
            typedef ListProto<NODE,PoolType,Container,ThreadingPolicy> CoreType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~BareList() noexcept {}

            //! [Releasable] release content
            inline virtual void release() noexcept { this->releaseList_(); }

        protected:
            //! setup empty
            inline explicit BareList() : CoreType(), Releasable() {}

            //! duplicate \param other another list
            inline BareList(const BareList &other) : CoreType(), Releasable()
            {
                this->duplicate(other);
            }

        private:
            Y_Disable_Assign(BareList); //!< discarding
        };

    }

}

#endif

