
//! \file

#ifndef Y_Ink_Local_Maxima_Included
#define Y_Ink_Local_Maxima_Included 1


#include "y/ink/histogram.hpp"
#include "y/ink/gradient.hpp"
#include "y/ink/edge/double-threshold.hpp"

namespace Yttrium
{
    namespace Ink
    {
        struct LocalMaxima
        {
            static const uint8_t Feeble = 127;
            static const uint8_t Strong = 255;

            static
            void Keep(Broker                & broker,
                      Histogram             & hist,
                      Pixmap<uint8_t>       & edge,
                      Pixmap<float>         & thin,
                      const Gradient<float> & grad);

            static
            void Part(Broker           & broker,
                      Pixmap<uint8_t>  & edge,
                      DoubleThreshold    part);


        };
    }

}


#endif // !Y_Ink_Local_Maxima_Included

