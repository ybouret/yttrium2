
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

        class Weasel:: FormulaToText : public Jive::Analyzer
        {
        public:
            explicit FormulaToText(const Jive::Syntax::Grammar &);
            virtual ~FormulaToText() noexcept;

            String compile(const Formula &, int &);

            Vector<String> stack;
            int            charge;

        private:
            Y_Disable_Copy_And_Assign(FormulaToText); //!< discarding
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
