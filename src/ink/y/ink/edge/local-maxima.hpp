
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

        //______________________________________________________________________
        //
        //
        //
        //! finding and marking local maxima
        //
        //
        //______________________________________________________________________
        struct LocalMaxima
        {
            static const uint8_t Feeble = 127; //!< alias
            static const uint8_t Strong = 255; //!< alias

            //! convert gradient map into thin borders, and build histogram
            /**
             \param broker broker
             \param hist   histogram of normalized gradient
             \param edge   quantized version of thin
             \param thin   local maxima of gradient only
             \param grad   pre-computed gradient
             */
            static
            void Keep(Broker                & broker,
                      Histogram             & hist,
                      Pixmap<uint8_t>       & edge,
                      Pixmap<float>         & thin,
                      const Gradient<float> & grad);

            //! convert current edge to 0/Feeble/Strong from histogram information
            /**
             \param broker broker
             \param edge   [in|out] edge indicator
             \param part computed from histogram
             */
            static
            void Part(Broker           & broker,
                      Pixmap<uint8_t>  & edge,
                      DoubleThreshold    part);


        };
    }

}


#endif // !Y_Ink_Local_Maxima_Included

