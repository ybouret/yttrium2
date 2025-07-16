
//! \file

#ifndef Y_Cameo_Genus_FPoint_Included
#define Y_Cameo_Genus_FPoint_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        class FPointGenus
        {
        public:
            static const char * const CallSign;

            virtual ~FPointGenus() noexcept;

        protected:
            explicit FPointGenus() noexcept;

        private:
            Y_Disable_Copy_And_Assign(FPointGenus);
        };
    }
}

#endif

