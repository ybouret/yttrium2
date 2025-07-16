
//! \file

#ifndef Y_Cameo_Genus_AProxy_Included
#define Y_Cameo_Genus_AProxy_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        class AProxyGenus
        {
        public:
            static const char * const CallSign;
            static void Overflow();

            virtual ~AProxyGenus() noexcept;

        protected:
            explicit AProxyGenus() noexcept;

        private:
            Y_Disable_Copy_And_Assign(AProxyGenus);
        };
    }
}

#endif

