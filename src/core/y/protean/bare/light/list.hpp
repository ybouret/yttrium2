//! \file

#ifndef Y_Protean_BareLightList_Included
#define Y_Protean_BareLightList_Included 1

#include "y/protean/bare/list.hpp"
#include "y/protean/node/light.hpp"
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! no cache, light list
        //
        //
        //______________________________________________________________________
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class BareLightList : public BareList<LightNode<T>,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef LightNode<T>                       NodeType; //!< alias
            typedef BareList<NodeType,ThreadingPolicy> BaseType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit BareLightList() : BaseType() {}

            //! cleanup
            inline virtual ~BareLightList() noexcept {}

            //! duplicate \param other another list
            inline BareLightList(const BareLightList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(BareLightList); //!< discarding

        };
    }

}

#endif
