
//! \file

#ifndef Y_Apex_SmartDev_Included
#define Y_Apex_SmartDev_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Device;

        //______________________________________________________________________
        //
        //
        //! Smart Pointer on Device
        //
        //______________________________________________________________________
        class SmartDev
        {
        public:
            explicit SmartDev(Device * const) noexcept; //!< register device
            virtual ~SmartDev()               noexcept; //!< delete device is no null

        protected:
            Device * const device; //!< inner device

        private:
            Y_Disable_Copy_And_Assign(SmartDev); //!< discarding
        };
    }

}

#endif // !Y_Apex_SmartDev_Included

