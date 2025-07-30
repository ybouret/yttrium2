
#include "y/coven/ilist.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(coven_indx)
{

    Coven::IPool pool;

    {
        Coven::IList     il(pool), is(pool);
        il << 7 << 2 << 4 << 1;
        std::cerr << il << std::endl;
        for(const Coven::INode *node=il->head;node;node=node->next)
        {
            is.sorted(**node);
        }
        std::cerr << is << std::endl;
    }

    std::cerr << "pool.size=" << pool.count() << std::endl;
    

}
Y_UDONE()

