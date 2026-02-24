//! \file

#ifndef Y_Ink_Filter_Gradient_Included
#define Y_Ink_Filter_Gradient_Included 1

#include "y/ink/filter.hpp"
#include "y/ink/gradient.hpp"
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //! use filter to compute gradient
        //
        //______________________________________________________________________
        template <typename T>
        struct FilterGradient
        {
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef V2D<T> vtx_t; //!< unit direction

            //! compute gradient
            /**
             \param broker broker
             \param gradient gradient
             \param filter   immediate: gy, transpose: gx
             \param source   source scalar pixmap
             */
            template <typename SCALAR> static inline
            void Compute(Broker               & broker,
                         Gradient<T>          & gradient,
                         const Filter<T>      & filter,
                         const Pixmap<SCALAR> & source)
            {
                broker.prep(gradient);
                broker.run(Run<SCALAR>,gradient,filter,source);
            }

        private:

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename SCALAR> static inline
            void Run(Lockable             &,
                     const Tile           & tile,
                     Gradient<T>          & gradient,
                     const Filter<T>      & filter,
                     const Pixmap<SCALAR> & source)
            {
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment s = tile[j];
                    Point         p = s.start;
                    for(unit_t i=s.width;i>0;--i,++p.x)
                        filter.loadGradient(gradient,gradient.dir,source,p);
                }
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_Ink_Filter_Gradient_Included
