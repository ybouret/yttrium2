

//! \file

#ifndef Y_Jive_Pattern_Or_Included
#define Y_Jive_Pattern_Or_Included 1

#include "y/jive/pattern/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(Or,Logic,'_', 'O','R','_'); //!< Enter: Or
        explicit Or()   noexcept;     //!< setup
        explicit Or(const Or &);      //!< duplicate
        Y_Jive_Pattern_API();
        Y_Jive_Pattern_End(Or);                         //!< Leave: Or
    }

}

#endif

