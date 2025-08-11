

//! \file

#ifndef Y_Jive_Syntax_InternalRule_Included
#define Y_Jive_Syntax_InternalRule_Included 1

#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Internal : public Rule
            {
            protected:
                template <typename RID> inline
                explicit Internal(const RID     &r,
                                  const uint32_t u) :
                Rule(r,IsInternal,u)
                {
                }

            public:

                virtual ~Internal() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Internal);
            };


        }
    }

}

#endif

