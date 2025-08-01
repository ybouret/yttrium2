
//! \file


#ifndef Y_Associative_DataBook_Included
#define Y_Associative_DataBook_Included 1

#include "y/protean/coop/heavy/list.hpp"

namespace Yttrium
{

    typedef  Protean::CoopHeavyList<uint64_t> DataList;
    typedef  DataList::PoolType               DataPool;
    typedef  DataList::NodeType               DataNode;
    
    class DataBook : public Ingress<const DataList>, public Recyclable
    {
    public:
        explicit DataBook(const DataPool &pool) noexcept;
        virtual ~DataBook() noexcept;

        virtual void free() noexcept;
        
        bool insert_(const uint64_t word);

    private:
        Y_Disable_Assign(DataBook);
        Y_Ingress_Decl();
        DataList list;
    };
}

#endif

