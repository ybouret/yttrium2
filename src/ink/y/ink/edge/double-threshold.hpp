

#ifndef Y_Ink_Double_Threshold_Included
#define Y_Ink_Double_Threshold_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Ink
    {
        class DoubleThreshold
        {
        public:
            DoubleThreshold(const uint8_t feebleValue,const uint8_t strongValue) noexcept;
            ~DoubleThreshold() noexcept;
            DoubleThreshold(const DoubleThreshold &) noexcept;
            Y_OSTREAM_PROTO(DoubleThreshold);


            const uint8_t feeble;
            const uint8_t strong;
            
        private:
            Y_Disable_Assign(DoubleThreshold);
        };
    }

}

#endif // !Y_Ink_Double_Threshold_Included
