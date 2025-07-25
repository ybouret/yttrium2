
#include "y/apex/api/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {
        IList:: IList(const IPoolType &pool) noexcept :
        IListType(pool)
        {}

        IList:: ~IList() noexcept {}

        IList:: IList(const IList &list) : IListType(list)
        {

        }
    }

}
