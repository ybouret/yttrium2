//! \file

#ifndef Y_Apex_Model_MulOps_Included
#define Y_Apex_Model_MulOps_Included 1

#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {

        struct MulOps
        {
            enum Case
            {
                Case00,
                Case01,
                Case0N,
                Case10,
                Case11,
                Case1N,
                CaseN0,
                CaseN1,
                CaseNN
            };

            static Case Get(const size_t lhs, const size_t rhs) noexcept;
        };



    }
}

#endif

