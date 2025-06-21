//! \file

#ifndef Y_Protean_BareHeavyLisr_Included
#define Y_Protean_BareHeavyLisr_Included 1

#include "y/protean/node/heavy.hpp"
#include "y/protean/bare/list.hpp"
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    namespace Protean
    {
        //______________________________________________________________________
        //
        //
        //
        //! no cache, heavy list
        //
        //
        //______________________________________________________________________
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class BareHeavyList : public BareList<HeavyNode<T>,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef HeavyNode<T>                       NodeType; //!< alias
            typedef BareList<NodeType,ThreadingPolicy> BaseType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit BareHeavyList() : BaseType() {}

            //! cleanup
            inline virtual ~BareHeavyList() noexcept {}

            //! duplicate \param other another heavy list
            inline BareHeavyList(const BareHeavyList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(BareHeavyList); //!< discarding
        };

    }

}

#endif
