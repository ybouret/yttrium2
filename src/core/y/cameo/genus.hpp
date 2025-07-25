//! \file

#ifndef Y_Cameo_Genus_Included
#define Y_Cameo_Genus_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //! base class for Genus
        class Genus
        {
        public:
            virtual ~Genus() noexcept; //!< cleanup

        protected:
            explicit Genus() noexcept; //!< setup

        private:
            Y_Disable_Copy_And_Assign(Genus); //!< discarding
        };
    }
}

#endif

