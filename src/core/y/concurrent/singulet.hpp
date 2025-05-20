
//! \file

#ifndef Y_Concurrent_Singulet_Included
#define Y_Concurrent_Singulet_Included 1

#include "y/system/at-exit.hpp"
#include "y/type/identifiable.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        
        class Singulet : public Identifiable
        {
        public:
            typedef System::AtExit::Longevity Longevity;
            static  const Longevity GreatestLongevity;

            virtual Longevity lifeTime() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(Singulet);
        };
    }
    

}


#endif

