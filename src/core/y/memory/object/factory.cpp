
#include "y/memory/object/factory.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            Factory:: ~Factory() noexcept
            {
            }

            Factory:: Factory() :
            FactoryAPI(PAGE_BYTES)
            {
            }

            void Factory:: display(std::ostream &, size_t) const
            {
            }


        }

    }

}
