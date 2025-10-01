
//! \file


#ifndef Y_Chemical_Weasel_FormulaTanslator_Included
#define Y_Chemical_Weasel_FormulaTanslator_Included 1

#include "y/chemical/weasel.hpp"
#include "y/jive/analyzer.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Chemical
    {



        //______________________________________________________________________
        //
        //
        //
        //! Translate formula to textual representation
        //
        //
        //______________________________________________________________________
        class Weasel:: FormulaTranslator : public Jive::Analyzer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char SubInit[]; //!< "<sub>"
            static const char SubQuit[]; //!< "</sub>"
            static const char SupInit[]; //!< "<sup>"
            static const char SupQuit[]; //!< "</sup>"

            //! conversion target
            enum Target
            {
                Text, //!< univocal text
                HTML, //!< univocal html label
                LaTeX //!< univocal latex expression
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormulaTranslator(const Jive::Syntax::Grammar &); //!< setup
            virtual ~FormulaTranslator() noexcept;                     //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return decoded to text or html
            String decode(const Formula &,
                          int * const,
                          const Target);

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Vector<String> stack;  //!< string stack
            int            charge; //!< charge state
            Target         target; //!< target choice


        private:
            Y_Disable_Copy_And_Assign(FormulaTranslator); //!< discarding

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void init();
            virtual void quit();
            virtual void show(const size_t) const;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            void onName(const Token &);
            void onCoef(const Token &);
            void onPlus(const Token&);
            void onMinus(const Token&);

            void onMult(const size_t);
            void onBody(const size_t);
            void onFormula(const size_t);
            void onZ(const size_t);
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
        };

    }

}

#endif // !Y_Chemical_Weasel_FormulaTanslator_Included
