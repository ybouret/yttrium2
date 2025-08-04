
//! \file

#ifndef Y_Jive_Pattern_Repeat_Included
#define Y_Jive_Pattern_Repeat_Included 1

#include "y/jive/pattern/joker.hpp"


namespace Yttrium
{
    namespace Jive
    {


        Y_Jive_Pattern_Decl(Repeat,Joker,'_', 'R','E','P');        //!< Enter:: Repeat
        explicit Repeat(const Motif &, const size_t)  noexcept;    //!< setup
        explicit Repeat(const Repeat &) noexcept;                  //!< duplicate
        Y_Jive_Pattern_API();

        const size_t minCount;
        Y_Jive_Pattern_End(Repeat); //!< Leave: Repeat
    }

}

#endif
