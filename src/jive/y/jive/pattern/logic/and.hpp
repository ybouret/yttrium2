
//! \file

#ifndef Y_Jive_Pattern_And_Included
#define Y_Jive_Pattern_And_Included 1

#include "y/jive/pattern/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(And,Logic,'_', 'A','N','D'); //!< Enter: And
        explicit And()   noexcept;     //!< setup
        explicit And(const And &);     //!< duplicate
        Y_Jive_Pattern_API();
        Y_Jive_Pattern_End(And);                         //!< Leave: And
    }

}

#endif

