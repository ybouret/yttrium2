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
        template <typename T>
        struct FilterGradient
        {
            typedef V2D<T> vtx_t;

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

        };

    }

}

#endif // !Y_Ink_Filter_Gradient_Included
