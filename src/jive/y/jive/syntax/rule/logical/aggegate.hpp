
//! \file

#ifndef Y_Jive_Syntax_Aggregate_Included
#define Y_Jive_Syntax_Aggregate_Included 1

#include "y/jive/syntax/rule/logical.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            class Aggregate : public Logical
            {
            public:
                static const uint32_t UUID = Y_FOURCC('A', 'G', 'G', '_');

                template <typename RID> inline
                explicit Aggregate(const RID &rid) :
                Logical(rid,UUID)
                {
                }


                virtual ~Aggregate() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Aggregate);
            };
        }

    }

}

#endif

