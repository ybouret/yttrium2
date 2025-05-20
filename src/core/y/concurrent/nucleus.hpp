
//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        class Nucleus : public Singulet
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime;
            virtual const char * callSign() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(Nucleus);
            explicit Nucleus();
            virtual ~Nucleus() noexcept;
        };
    }

}

#endif

