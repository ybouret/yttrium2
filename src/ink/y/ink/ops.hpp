
//! \file

#ifndef Y_Ink_Ops_Included
#define Y_Ink_Ops_Included 1

#include "y/ink/pixmap.hpp"
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        struct Ops
        {

            template <
            typename PIXMAP,
            typename PROC> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap);
            }

            
        };

    }

}

#endif // !Y_Ink_Ops_Included
