
//! \file

#ifndef Y_Jive_Lexical_Design_Included
#define Y_Jive_Lexical_Design_Included 1

#include "y/jive/lexical/no-data.hpp"
#include "y/jive/pattern/dictionary.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            class Design
            {
            public:
                explicit Design();
                explicit Design(const Design &) noexcept;
                virtual ~Design() noexcept;

                const Dictionary::Pointer pdb;
                const NoData              nil;

            private:
                Y_Disable_Assign(Design);
            };
        }

    }

}

#endif
