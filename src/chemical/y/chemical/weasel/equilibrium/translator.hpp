
//! \file


#ifndef Y_Chemical_Weasel_EqTrans_Included
#define Y_Chemical_Weasel_EqTrans_Included 1

#include "y/chemical/weasel.hpp"
#include "y/chemical/library.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Translate node into equilibrium
        //
        //
        //______________________________________________________________________
        class Weasel:: EquilibriumTranslator
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit EquilibriumTranslator();          //!< setup
            virtual ~EquilibriumTranslator() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return new equilibrium fron node
            Equilibrium * decode(const XNode * const,Library &, const size_t,Lua::VM &);

        private:
            Y_Disable_Copy_And_Assign(EquilibriumTranslator); //!< discarding

            //! decode reac/prod
            void decode(const String &,
                        Actor::List  &,
                        const XNode * const,
                        Library     &);
        };
    }

}

#endif

