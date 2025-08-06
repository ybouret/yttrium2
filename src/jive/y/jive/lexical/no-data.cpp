
#include "y/jive/lexical/no-data.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            NoData:: ~NoData() noexcept
            {
            }

            NoData:: NoData() : tag("") {}
            NoData:: NoData(const NoData &_) noexcept : tag(_.tag) {}

        }

    }

}
