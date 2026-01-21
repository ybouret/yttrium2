
//! \file

#ifndef Y_Ink_Ops_Included
#define Y_Ink_Ops_Included 1

#include "y/ink/pixmap.hpp"
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //! Seq/Par operations wrapper
        struct Ops
        {
            //! apply unary operation to each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel)
             \param pixmap source/taget pixmap
             */
            template <
            typename PIXMAP,
            typename PROC> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap);
            }


            //! apply binary operation on each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel,arg1)
             \param pixmap source/taget pixmap
             \param arg1   argument for proc
             */
            template <
            typename PIXMAP,
            typename PROC,
            typename ARG1> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap, ARG1 &arg1 ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap,arg1);
            }

            //! apply ternary operation on each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel,arg1,arg2)
             \param pixmap source/target pixmap
             \param arg1   argument for proc
             \param arg2   argument for proc
             */
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
