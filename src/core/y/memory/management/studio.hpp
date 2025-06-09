
//! \file

#ifndef Y_Memory_Studio_Included
#define Y_Memory_Studio_Included 1


#include "y/memory/management/inferno.hpp"
#include "y/singleton.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T,const System::AtExit::Longevity LIFE_TIME>
        class Studio : public Singleton<Studio<T,LIFE_TIME>,ClassLockPolicy>, public Inferno<T>
        {
        public:

            static const char * const              CallSign;
            static const System::AtExit::Longevity LifeTime = LIFE_TIME;

        private:
            Y_Disable_Copy_And_Assign(Studio);
        };
    }
}

#endif

