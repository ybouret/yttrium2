
//! \file

#ifndef Y_Cameo_Genus_AProxy_Included
#define Y_Cameo_Genus_AProxy_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        //! Genus for AProxy types
        class AProxyGenus : public Genus
        {
        public:
            static const char * const CallSign; //!< "AProxy"
            static void Overflow();             //!< throw on overflow
            virtual ~AProxyGenus() noexcept;    //!< cleanup
        protected:
            explicit AProxyGenus() noexcept;    //!< setup
        private:
            Y_Disable_Copy_And_Assign(AProxyGenus); //!< discarding
        };
    }
}

#endif // !Y_Cameo_Genus_AProxy_Included

