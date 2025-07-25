
#include "y/apex/api/coven/iset.hpp"


namespace Yttrium
{

    namespace Coven
    {
        ISet:: ~ISet() noexcept
        {
        }

        ISet:: ISet(const IPoolType &pool ) noexcept :
        Ingress<const IList>(),
        list(pool)
        {
        }

        ISet:: ISet(const ISet &other) :
        Ingress<const IList>(),
        list(other.list)
        {
        }

        ISet::ConstInterface & ISet:: locus() const noexcept
        {
            return list;
        }

        static inline SignType CompareNodes(const INode * const lhs, const INode * const rhs) noexcept
        {
            return Sign::Of( **lhs, **rhs );
        }

        ISet & ISet:: operator<<(INode * const node)
        {
            Core::ListOf<INode> rhs; rhs.pushTail(node);
            Core::ListOf<INode> &lhs = *list;
            Core::ListOf<INode> output;

            output.fusion(lhs,rhs,CompareNodes);
            lhs.swapListFor(output);
            
            return *this;
        }


        bool ISet:: has(const size_t indx) const noexcept
        {
            for(const INode *node=list->head;node;node=node->next)
            {
                if( indx == **node ) return true;
            }
            return false;
        }



    }

}
