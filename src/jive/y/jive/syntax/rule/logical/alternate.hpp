

//! \file

#ifndef Y_Jive_Syntax_Alternate_Included
#define Y_Jive_Syntax_Alternate_Included 1

#include "y/jive/syntax/rule/logical.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            class Alternate : public Logical
            {
            public:
                static const uint32_t UUID = Y_FOURCC('A', 'L', 'T', '_');

                template <typename RID> inline
                explicit Alternate(const RID &rid) :
                Logical(rid,UUID)
                {
                }


                virtual ~Alternate() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Alternate);
            };
        }

    }

}

#endif

