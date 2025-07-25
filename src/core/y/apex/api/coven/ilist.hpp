//! \file

#ifndef Y_Coven_IList_Included
#define Y_Coven_IList_Included 1

#include "y/protean/coop/heavy/list.hpp"


namespace Yttrium
{

    namespace Coven
    {

        typedef Protean::CoopHeavyList<size_t,SingleThreadedClass> IListType;
        typedef IListType::PoolType                                IPoolType;
        typedef IListType::NodeType                                INode;

        class IList : public IListType
        {
        public:
            explicit IList(const IPoolType &) noexcept;
            virtual ~IList() noexcept;
            IList(const IList &);
            
        private:
            Y_Disable_Assign(IList);
        };

        

    }

}
#endif

