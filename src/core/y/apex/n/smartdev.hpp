
//! \file

#ifndef Y_Apex_SmartDev_Included
#define Y_Apex_SmartDev_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Device;

        class SmartDev
        {
        public:
            explicit SmartDev(Device * const) noexcept;
            virtual ~SmartDev()               noexcept;

        protected:
            Device * const device;

        private:
            Y_Disable_Copy_And_Assign(SmartDev);
        };
    }

}

#endif

