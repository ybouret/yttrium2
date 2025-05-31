
#include "y/memory/object/factory.hpp"
#include "y/xml/attribute.hpp"
#include <iostream>

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

            void Factory:: display(std::ostream &os, size_t indent) const
            {
                initProlog(os, indent);
                os << Attribute("LifeTime",LifeTime);
                initEpilog(os);
            }


        }

    }

}
