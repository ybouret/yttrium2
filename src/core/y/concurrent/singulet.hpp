
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
            static  bool                      Verbose;
            typedef System::AtExit::Longevity Longevity;
            static  const Longevity           GreatestLifeTime = IntegerFor<Longevity>::Maximum;

            explicit Singulet() noexcept;
            virtual ~Singulet() noexcept;
            virtual Longevity lifeTime() const noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Singulet);
        };
    }
    

}


#endif

