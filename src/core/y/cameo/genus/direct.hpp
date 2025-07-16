//! \file

#ifndef Y_Cameo_Genus_Direct_Included
#define Y_Cameo_Genus_Direct_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        class DirectGenus
        {
        public:
            static const char * const CallSign;

            virtual ~DirectGenus() noexcept;

        protected:
            explicit DirectGenus() noexcept;

        private:
            Y_Disable_Copy_And_Assign(DirectGenus);
        };
    }
}

#endif

