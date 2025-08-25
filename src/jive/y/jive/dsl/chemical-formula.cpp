#include "y/jive/dsl/chemical-formula.hpp"

namespace Yttrium
{
    namespace Jive
    {
        ChemicalFormula:: ~ChemicalFormula() noexcept
        {

        }


        const char * const ChemicalFormula:: Name     = "ChemicalFormula::Name";
        const char * const ChemicalFormula:: Body     = "ChemicalFormula::Body";
        const char * const ChemicalFormula:: Mult     = "ChemicalFormula::Mult";
        const char * const ChemicalFormula:: CoefExpr = "[:digit:]+";
        const char * const ChemicalFormula:: OptCoef  = "ChemicalFormula::OptCoef";
        const char * const ChemicalFormula:: Item     = "ChemicalFormula::Item";
        const char * const ChemicalFormula:: Sign     = "ChemicalFormula::Sign";
        const char * const ChemicalFormula:: Z        = "ChemicalFormula::Z";


        const Syntax::Rule & ChemicalFormula:: install(Parser &p)
        {
            const Rule * const coef = p.queryRule("COEF");
            if(!coef) throw Specific::Exception(lang->c_str(),"need COEFF from %s Parser",p.lang->c_str());

            Agg &FORMULA = p.agg(lang);

            //------------------------------------------------------------------
            //
            // Common rules for Equilibria/Formula
            //
            //------------------------------------------------------------------

            const Rule &COEF      = *coef;
            const Rule &OPT_COEF  = p.opt(OptCoef,COEF); // specific optional coeff
            const Rule &PLUS      = p.term('+');
            const Rule &MINUS     = p.term('-');
            const Rule &SIGN      = (p.alt(Sign) << MINUS << PLUS);


            //------------------------------------------------------------------
            //
            // Create Formula
            //
            //------------------------------------------------------------------
            {
                const Rule &NAME = p.term(Name,"[:upper:][[:lower:]_]*");
                Agg        &MULT = p.act(Mult);
                const Rule &BODY = p.act(Body) << MULT << p.zom(MULT);
                Alt        &ITEM = p.alt("Item");
                MULT    << ITEM     << OPT_COEF;
                ITEM    << NAME     << p.parens(BODY);
                FORMULA << BODY << p.opt(p.agg(Z) << '^' << OPT_COEF << SIGN);
            }

            return FORMULA;
        }

    }
}

#include "y/jive/analyzer.hpp"

namespace Yttrium
{
    namespace Jive
    {

        class ChemicalFormula:: ToText:: Code : public Analyzer
        {
        public:
            inline explicit Code(const Syntax::Grammar &G) : Analyzer(G,Permissive)
            {
                verbose = true;
            }

            inline virtual ~Code() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
            virtual void init()
            {
            }

            virtual void quit()
            {
            }

        };

#define Y_Push(ID) Y_Jive_Push(Code,ID)
#define Y_Func(ID) Y_Jive_Func(Code,ID)
        

        ChemicalFormula:: ToText:: ToText(const Syntax::Grammar &G) :
        code( new Code(G) )
        {
        }



        ChemicalFormula:: ToText:: ~ToText() noexcept
        {
            Destroy(code);
        }

        String  ChemicalFormula:: ToText:: operator()(const XNode * const root)
        {
            assert(0!=root);
            assert(0!=code);
            code->walk(root);
            return String();
        }


    }

}

