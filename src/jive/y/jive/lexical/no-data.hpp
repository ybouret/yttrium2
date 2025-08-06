
//! \file

#ifndef Y_Jive_Lexical_NoData_Included
#define Y_Jive_Lexical_NoData_Included 1

#include "y/jive/tag.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            class NoData
            {
            public:
                NoData();
                NoData(const NoData &) noexcept;
                ~NoData() noexcept;

                const Tag tag;

            private:
                Y_Disable_Assign(NoData);
            };
        }

    }

}

#endif

