

//! \file

#ifndef Y_Protean_CoopLightList_Included
#define Y_Protean_CoopLightList_Included 1

#include "y/protean/coop/list.hpp"
#include "y/protean/node/light.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! Light List with shared cache
        //
        //
        //______________________________________________________________________
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class CoopLightList : public CoopList<LightNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef LightNode<T>                                            NodeType; //!< alias
            typedef CoopList<NodeType,CommonContainer,ThreadingPolicy>      BaseType; //!< alias
            typedef typename BaseType::PoolType                             PoolType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param shared shared cache
            inline explicit CoopLightList(const PoolType &shared) : BaseType(shared) {}

            //! cleanup
            inline virtual ~CoopLightList() noexcept {}

            //! duplicate with same shared cache \param other another list
            inline CoopLightList(const CoopLightList &other) :
            Container(), BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(CoopLightList); //!< discarding

        };
    }

}

#endif
