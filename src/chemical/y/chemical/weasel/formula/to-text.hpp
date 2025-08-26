
//! \file


#ifndef Y_Chemical_Weasel_FormulaToText_Included
#define Y_Chemical_Weasel_FormulaToText_Included 1

#include "y/chemical/weasel.hpp"
#include "y/jive/analyzer.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        class Weasel:: FormulaTranslator : public Jive::Analyzer
        {
        public:
            explicit FormulaTranslator(const Jive::Syntax::Grammar &);
            virtual ~FormulaTranslator() noexcept;

            String decode(const Formula &, int &);

            Vector<String> stack;
            int            charge;

        private:
            Y_Disable_Copy_And_Assign(FormulaTranslator); //!< discarding
            virtual void init();
            virtual void quit();
            virtual void show(const size_t) const;

            void onName(const Token &);
            void onCOEF(const Token &);
            void onPlus(const Token&);
            void onMinus(const Token&);

            void onMult(const size_t);
            void onBody(const size_t);
            void onFormula(const size_t);
            void onZ(const size_t);
        };

    }

}

#endif
