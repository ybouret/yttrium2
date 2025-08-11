
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            class Rule : public Object
            {
            protected:
                template <typename RID> inline
                explicit Rule(const RID     &r,
                              const Category t,
                              const uint32_t u) :
                name(r),
                type(t),
                uuid(u)
                {
                }
                
            public:
                virtual ~Rule() noexcept;

                const Tag      name;
                const Category type;
                const uint32_t uuid;

            private:
                Y_Disable_Copy_And_Assign(Rule);
            };
        }
    }

}

#endif

