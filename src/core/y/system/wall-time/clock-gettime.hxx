#include <time.h>
#include <sys/time.h>
#include <cerrno>

#    define Y_CLOCK_ID CLOCK_REALTIME
#    if defined(Y_SunOS)
#        undef  Y_CLOCK_ID
#        define Y_CLOCK_ID CLOCK_HIGHRES
#    endif

namespace Yttrium
{
    namespace System
    {
        static const uint64_t __giga64 = 0x3B9ACA00;

        class WallTime :: Code : public Object
        {
            public:
            inline explicit Code() : Object(), freq( Calibrate() )
            {}

            inline virtual ~Code() noexcept 
            {

            }

            inline long double convert(const uint64_t ticks) const noexcept 
            {
                return freq * static_cast<long double>(ticks);
            }

            const long double freq;

            private:
            Y_Disable_Copy_And_Assign(Code);
            static inline long double Calibrate()
            {
                static const long double nano = 1.0e-9L;
                Y_Giant_Lock();
                struct timespec tp  = { 0, 0 };
                const int       err = clock_getres(Y_CLOCK_ID,&tp);
                if(err!=0) throw Libc::Exception( errno, "clock_getres" );
                //std::cerr << "tp: " << tp.tv_sec << "s  " << tp.tv_nsec << " ns" << std::endl;
                return  nano * static_cast<long double>(__giga64*uint64_t(tp.tv_sec) + uint64_t(tp.tv_nsec));
            }
        };

        uint64_t WallTime:: Ticks()
        {
            struct timespec tp  = { 0, 0 };
            const int       err = clock_gettime( Y_CLOCK_ID, &tp );
            if(err!=0)
                throw Libc::Exception( errno, "clock_gettime" );
            return __giga64*uint64_t(tp.tv_sec) + uint64_t(tp.tv_nsec);
        }

    }
}