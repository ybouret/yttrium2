
//! \file

#ifndef Y_Protean_SoloLightList_Included
#define Y_Protean_SoloLightList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/light.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! Light list with its own cache
        //
        //
        //______________________________________________________________________
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class SoloLightList : public SoloList<LightNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef LightNode<T>                                       NodeType; //!< alias
            typedef SoloList<NodeType,CommonContainer,ThreadingPolicy> BaseType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit SoloLightList() : BaseType() {} //!< setup empty
            inline virtual ~SoloLightList() noexcept {}     //!< cleanup

            //! duplicate with own cache \param other another list
            inline SoloLightList(const SoloLightList &other) : Container(), BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(SoloLightList); //!< discarding

        };
    }

}

#endif
