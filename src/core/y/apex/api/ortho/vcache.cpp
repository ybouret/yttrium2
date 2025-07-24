
#include "y/apex/api/ortho/vcache.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            VCache:: ~VCache() noexcept
            {
            }

            VCache:: VCache(const Metrics &metrics) :
            Metrics(metrics),
            list()
            {
            }

            Vector * VCache:: query()
            {
                return list.size ? list.popTail() : new Vector(*this);
            }

            void VCache:: store(Vector *const vec) noexcept
            {
                assert(0!=vec);
                assert(dimensions == vec->dimensions);
                list.pushHead(vec)->ldz();
            }

        }

    }

}


