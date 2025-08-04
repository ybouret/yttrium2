//! \file

#ifndef Y_Jive_Pattern_Option_Included
#define Y_Jive_Pattern_Option_Included 1

#include "y/jive/pattern/joker.hpp"


namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(Option,Joker,'_', 'O','P','T'); //!< Enter:: Option
        explicit Option(const Motif &)  noexcept;     //!< setup
        explicit Option(const Option &) noexcept;     //!< duplicate
        Y_Jive_Pattern_API();

        Y_Jive_Pattern_End(Option); //!< Leave: Option
    }

}

#endif
