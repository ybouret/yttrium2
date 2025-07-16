
//! \file

#ifndef Y_Cameo_Genus_FPoint_Included
#define Y_Cameo_Genus_FPoint_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        //! Genus for FPoint types
        class FPointGenus : public Genus
        {
        public:
            static const char * const CallSign; //!< "FPoint
            virtual ~FPointGenus() noexcept;    //!< cleanup
        protected:
            explicit FPointGenus() noexcept;    //!< setup
        private:
            Y_Disable_Copy_And_Assign(FPointGenus); //!< discarding
        };
    }
}

#endif

