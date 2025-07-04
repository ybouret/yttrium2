//! \file

#ifndef Y_Apex_Model_MulOps_Included
#define Y_Apex_Model_MulOps_Included 1

#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //! detecting Mul/Div case
        struct MulOps
        {
            //! possible cases
            enum Case
            {
                Case00, //!< zero / zero
                Case01, //!< zero / one
                Case0N, //!< zero /  >one
                Case10, //!< one  / zero
                Case11, //!< one  / one
                Case1N, //!< one  /  >one
                CaseN0, //!< >one / zero
                CaseN1, //!< >one / one
                CaseNN  //!< >one /  >one
            };

            //! \return case according to bits/value
            static Case Get(const size_t, const size_t) noexcept;
        };



    }
}

#endif

