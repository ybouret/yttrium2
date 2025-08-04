


//! \file

#ifndef Y_Jive_Pattern_None_Included
#define Y_Jive_Pattern_None_Included 1

#include "y/jive/pattern/logic.hpp"

namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(None,Logic,'N', 'O','N','E'); //!< Enter: None
        explicit None()   noexcept;     //!< setup
        explicit None(const None &);    //!< duplicate
        Y_Jive_Pattern_API();
        Y_Jive_Pattern_End(None);                         //!< Leave: None
    }

}

#endif

