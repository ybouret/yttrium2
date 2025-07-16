
//! \file

#ifndef Y_Cameo_Genus_Vectorial_Included
#define Y_Cameo_Genus_Vectorial_Included 1

#include "y/cameo/genus.hpp"

namespace Yttrium
{
    namespace Cameo
    {
        //! Genus for vectorial types
        class VectorialGenus : public Genus
        {
        public:
            virtual ~VectorialGenus() noexcept; //!< cleanup

        protected:

            //! setup \param sid scalar identfier
            explicit VectorialGenus(const char * const sid) noexcept;

            //! Vectorial+sid
            const char identifier[16];

        private:
            Y_Disable_Copy_And_Assign(VectorialGenus); //!< discarding
        };
    }
}

#endif
