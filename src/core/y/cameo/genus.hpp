//! \file

#ifndef Y_Cameo_Genus_Included
#define Y_Cameo_Genus_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        class Genus
        {
        public:
            virtual ~Genus() noexcept;

        protected:
            explicit Genus() noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(Genus);
        };
    }
}

#endif

