//! \file

#ifndef Y_Ink_Double_Threshold_Included
#define Y_Ink_Double_Threshold_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! double threshold values
        //
        //
        //______________________________________________________________________
        class DoubleThreshold
        {
        public:
            //! setup \param feebleValue feeble \param strongValue strong
            DoubleThreshold(const uint8_t feebleValue,const uint8_t strongValue) noexcept;
            ~DoubleThreshold()                       noexcept; //!< cleanup
            DoubleThreshold(const DoubleThreshold &) noexcept; //!< duplicate
            Y_OSTREAM_PROTO(DoubleThreshold);                  //!< display


            const uint8_t feeble; //!< 0 below feeble, LocalMaxim::Feeble otherwise
            const uint8_t strong; //!< LocalMaxima::Strong if above

        private:
            Y_Disable_Assign(DoubleThreshold); //!< discarding
        };
    }

}

#endif // !Y_Ink_Double_Threshold_Included
