


//! \file

#ifndef Y_Protean_CoopHeavList_Included
#define Y_Protean_CoopHeavList_Included 1

#include "y/protean/coop/list.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/container/sequence.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! Cooperative Heavy List
        //
        //
        //______________________________________________________________________
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class CoopHeavyList : public CoopList<HeavyNode<T>,Sequence<T,CommonContainer>,ThreadingPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef HeavyNode<T>                                    NodeType;     //!< aliases
            typedef Sequence<T,CommonContainer>                     SequenceType; //!< aliases
            typedef CoopList<NodeType,SequenceType,ThreadingPolicy> BaseType;     //!< aliases
            typedef typename BaseType::PoolType                     PoolType;     //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setupe empty \param shared shared pool
            inline explicit CoopHeavyList(const PoolType &shared) : BaseType(shared) {}

            //! cleanup
            inline virtual ~CoopHeavyList() noexcept {}

            //! assign cache and duplicate \param other another list
            inline CoopHeavyList(const CoopHeavyList &other) : Container(), BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(CoopHeavyList); //!< discard

        };
    }

}

#endif
