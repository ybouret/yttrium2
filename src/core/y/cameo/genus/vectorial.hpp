
//! \file

#ifndef Y_Cameo_Genus_Vectorial_Included
#define Y_Cameo_Genus_Vectorial_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        class VectorialGenus
        {
        public:

            virtual ~VectorialGenus() noexcept;

        protected:
            explicit VectorialGenus(const char * const sid) noexcept;

            const char identifier[16];

        private:
            Y_Disable_Copy_And_Assign(VectorialGenus);
        };
    }
}

#endif
