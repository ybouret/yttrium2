
//! \file

#ifndef Y_Apex_Device_Included
#define Y_Apex_Device_Included 1

#include "y/apex/k/parcels.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    namespace Apex
    {

        class Device : public Object, public Parcels
        {
        public:

            explicit Device(const size_t   userBlockSize,
                            const PlanType userBlockPlan);
            Device(const Device &);
            virtual ~Device() noexcept;

            void shr() noexcept;

            const size_t   bits;  //!< current bits
            const size_t & bytes; //!< current bytes in Plan8
            const size_t & space; //!< in bytes
            
        private:
            Y_Disable_Assign(Device);
        };


    }

}

#endif
