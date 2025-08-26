
//! \file


#ifndef Y_Chemical_Assembly_Included
#define Y_Chemical_Assembly_Included 1


#include "y/chemical/type/entity.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Assembly
        {
        public:
            explicit Assembly() noexcept;
            virtual ~Assembly() noexcept;

            
        private:
            Y_Disable_Copy_And_Assign(Assembly);
        };


    }

}

#endif

