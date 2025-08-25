// \file

#ifndef Y_Jive_Chemical_Formula_Included
#define Y_Jive_Chemical_Formula_Included 1

#include "y/jive/parser.hpp"

namespace Yttrium
{

    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Chemical Formula Description
        //
        //
        //______________________________________________________________________
        class ChemicalFormula : public DSL
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id identifier for context
            template <typename ID> inline
            explicit ChemicalForumal(const ID & id ) : DSL(id) {}
            virtual ~ChemicalFormula() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________


        private:
            Y_Disable_Copy_And_Assign(DSL); //!< discarding
        };
    }

}

#endif

