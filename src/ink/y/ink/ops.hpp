
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


            template <
            typename PIXMAP,
            typename PROC,
            typename ARG1> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap, ARG1 &arg1 ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap,arg1);
            }

            template <
            typename PIXMAP,
            typename PROC,
            typename ARG1,
            typename ARG2> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap, ARG1 &arg1, ARG2 &arg2) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap,arg1,arg2);
            }

        };

    }

}

#endif // !Y_Ink_Ops_Included
