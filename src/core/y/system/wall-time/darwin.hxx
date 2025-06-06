
#include <mach/mach.h>
#include <mach/mach_time.h>
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace System
    {

        class WallTime:: Code : public Object
        {
        public:
            explicit Code() : Object(), freq( Calibrate() )
            {
            }

            virtual ~Code() noexcept
            {
            }

            inline long double convert(const uint64_t ticks) const noexcept
            {
                return static_cast<long double>(ticks) * freq;
            }

            const long double freq;

        private:
            Y_Disable_Copy_And_Assign(Code);
            static inline long double Calibrate()
            {
                static const long double nano = 1.0e-9L;
                Y_Giant_Lock();
                mach_timebase_info_data_t timebase;
                const kern_return_t       err = mach_timebase_info(&timebase);
                if(KERN_SUCCESS!=err)
                {
                    throw Mach::Exception(err,"mach_timebase_info");
                }
                const long double  conversion_factor = static_cast<long double>(timebase.numer) / timebase.denom;
                return nano * conversion_factor;

            }
        };

        uint64_t WallTime:: Ticks()
        {
            return mach_absolute_time();
        }

    }

}

