//! \file

#ifndef Y_Cameo_Genus_Direct_Included
#define Y_Cameo_Genus_Direct_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //! Genus for Direct types
        class DirectGenus : public Genus
        {
        public:
            static const char * const CallSign; //!< "Direct
            virtual ~DirectGenus() noexcept;    //!< cleanup
        protected:
            explicit DirectGenus() noexcept;    //!< setup

        private:
            Y_Disable_Copy_And_Assign(DirectGenus); //!< discarding
        };
    }
}

#endif

