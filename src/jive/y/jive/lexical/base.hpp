
//! \file

#ifndef Y_Jive_Lexical_Base_Included
#define Y_Jive_Lexical_Base_Included 1

#include "y/jive/lexical/no-data.hpp"
#include "y/jive/pattern/dictionary.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class Base
            {
            public:
                explicit Base();
                virtual ~Base() noexcept;

                const Dictionary::Pointer pdb;
                const NoData              nil;

            private:
                Y_Disable_Copy_And_Assign(Base);
            };
        }

    }

}

#endif
