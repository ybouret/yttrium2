// \file

#ifndef Y_Jive_Chemical_Formula_Included
#define Y_Jive_Chemical_Formula_Included 1

#include "y/jive/dsl.hpp"

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
            static const char * const Name;      //!< "ChemicalFormula::Name"
            static const char * const Body;      //!< "ChemicalFormula::Body"
            static const char * const Mult;      //!< "ChemicalFormula::Mult"
            static const char * const Coef;      //!< "COEF", external definition
            static const char * const CoefExpr;  //!< "[:digit:]+"
            static const char * const OptCoef;   //!< "ChemicalFormula::OptCoef"
            static const char * const Item;      //!< "ChemicalFormula::Item"
            static const char * const Sign;      //!< "ChemicalFormula::Sign"
            static const char * const Z;         //!< "ChemicalFormula::Z"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id identifier for context
            template <typename ID> inline
            explicit ChemicalFormula(const ID   &id) : DSL(id) {}
            virtual ~ChemicalFormula() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! parser must have a 'const Rule & COEF = term("COEF",CoefExpr)'
            const Rule & install( Parser & );


        private:
            Y_Disable_Copy_And_Assign(ChemicalFormula); //!< discarding

        public:
            class ToText  
            {
            public:
                explicit ToText(const Syntax::Grammar &);
                virtual ~ToText() noexcept;

                String operator()(const XNode * const root);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(ToText);
                Code * const code;
                
            };
        };
    }

}

#endif

