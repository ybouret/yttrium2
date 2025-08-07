//! \file

#ifndef Y_Jive_Lexical_Comment_Included
#define Y_Jive_Lexical_Comment_Included 1

#include "y/jive/lexical/scanner.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            class Comment : public Scanner
            {
            protected:
                
            public:
                virtual ~Comment() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Comment);


            };

        }

    }

}
#endif

