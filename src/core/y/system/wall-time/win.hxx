#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Yttrium
{
    namespace System
    {

        class WallTime::Code : public Object
        {
        public:
            explicit Code() : Object(), freq(Calibrate())
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
                Y_Giant_Lock();
                LARGE_INTEGER f;
                if (!::QueryPerformanceFrequency(&f))
                    throw Windows::Exception(::GetLastError(), "::QueryPerformanceFrequency()");
                return 1.0L / static_cast<long double>(f.QuadPart);

            }
        };

        uint64_t WallTime::Ticks()
        {
            LARGE_INTEGER t;
            if (!::QueryPerformanceCounter(&t))
                throw Windows::Exception(::GetLastError(), "::QueryPerformanceCounter()");
            return  uint64_t(t.QuadPart);
        }

    }

}
