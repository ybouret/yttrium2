

//! \file


#ifndef Y_Concurrent_Subdivision_Included
#define Y_Concurrent_Subdivision_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Subdivision
        {
        public:
            static const char * const Empty; //!< "|empty|";


        protected:
            explicit Subdivision() noexcept;

        public:
            virtual ~Subdivision() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Subdivision);
        };
    }

}

#endif // !Y_Concurrent_Subdivision_Included
