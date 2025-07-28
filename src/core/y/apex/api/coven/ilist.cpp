
#include "y/apex/api/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {
        IList:: IList(const IPool &pool) noexcept :
        IListType(pool)
        {}

        IList:: ~IList() noexcept {}

        IList:: IList(const IList &list) :
        Container(),
        IListType(list)
        {

        }

        IList:: IList(const IPool &pool, const size_t n, const size_t first) :
        Container(),
        IListType(pool)
        {
            assert(n>0);
            assert(first>0);
            assert(first<=n);

            size_t j = first;
            for(size_t i=n;i>0;--i,++j)
            {
                if(j>n) j=1;
                (*this) << j;
            }
        }


        void IList:: remove(const size_t indx) noexcept
        {
            for(INode *node = list.head;node;node=node->next)
            {
                if(indx==**node)
                {
                    cut(node);
                    return;
                }
            }

        }

        static inline SignType CompareData(const INode * const lhs, const INode * const rhs) noexcept
        {
            return Sign::Of(**lhs,**rhs);
        }

        void IList:: sorted(const size_t indx)
        {
            list.insertOrderedBy(CompareData,pool.summon(indx));
        }
        
        bool operator==(const IList &lhs, const IList &rhs) noexcept
        {
            if(lhs->size != rhs->size) return false;

            for(const INode *l=lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
            {
                assert(l);assert(r);
                if( **l != **r ) return false;
            }

            return true;
        }


        bool operator!=(const IList &lhs, const IList &rhs) noexcept
        {
            if(lhs->size != rhs->size) return true;

            for(const INode *l=lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
            {
                assert(l);assert(r);
                if( **l != **r ) return true;
            }

            return false;
        }




        SignType IList:: Compare(const IList &lhs, const IList &rhs) noexcept
        {

            switch( Sign::Of(lhs->size,rhs->size) )
            {
                case Negative: return Negative;
                case Positive: return Positive;
                case __Zero__: break;

            }

            for(const INode *l=lhs->head, *r=rhs->head;l;l=l->next,r=r->next)
            {
                assert(l);assert(r);
                switch( Sign::Of(**l,**r) )
                {
                    case Negative: return Negative;
                    case Positive: return Positive;
                    case __Zero__: continue;
                }
            }
            
            return __Zero__;
        }


    }

}
