

//! \file

#ifndef Y_Jive_Pattern_Amount_Included
#define Y_Jive_Pattern_Amount_Included 1

#include "y/jive/pattern/joker.hpp"


namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(Amount,Joker,'A', 'M','N','T');        //!< Enter:: Repeat
        explicit Amount(const Motif &, const size_t, const size_t); //!< setup
        explicit Amount(const Amount &) noexcept;                  //!< duplicate
        Y_Jive_Pattern_API();

        const size_t minCount;
        const size_t maxCount;
        Y_Jive_Pattern_End(Amount); //!< Leave: Repeat
    }

}

#endif
