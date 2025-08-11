
//! \file

#ifndef Y_Jive_Syntax_Logical_Included
#define Y_Jive_Syntax_Logical_Included 1

#include "y/jive/syntax/rule/internal.hpp"
#include "y/protean/bare/light/list.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            typedef Protean::BareLightList<Rule> Manifest;

            class Logical : public Internal, public Manifest
            {
            protected:
                template <typename RID> inline
                explicit Logical(const RID &r, const uint32_t u) :
                Internal(r,u),
                Manifest()
                {
                    
                }

            public:
                virtual ~Logical() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Logical);
            };

        }

    }

}

#endif

