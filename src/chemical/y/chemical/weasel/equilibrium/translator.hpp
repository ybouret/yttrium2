
//! \file


#ifndef Y_Chemical_Weasel_EqTrans_Included
#define Y_Chemical_Weasel_EqTrans_Included 1

#include "y/chemical/weasel.hpp"
#include "y/chemical/library.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        class Weasel:: EquilibriumTranslator
        {
        public:
            explicit EquilibriumTranslator(); //!< setup
            virtual ~EquilibriumTranslator() noexcept;                     //!< cleanup

            Equilibrium * decode(const XNode * const,
                                 Library &      lib,
                                 const size_t   top,
                                 Lua::VM       &lvm);

        private:
            Y_Disable_Copy_And_Assign(EquilibriumTranslator);
            

            void decode(const String &,
                        Actor::List  &,
                        const XNode * const,
                        Library     &);
        };
    }

}

#endif

