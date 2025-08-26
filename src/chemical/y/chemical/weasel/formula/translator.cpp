
#include "y/chemical/weasel/formula/translator.hpp"
#include "y/format/decimal.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{

    namespace Chemical
    {

#define Y_Push(ID) Y_Jive_Push(FormulaTranslator,ID)
#define Y_Func(ID) Y_Jive_Func(FormulaTranslator,ID)

        Weasel:: FormulaTranslator:: FormulaTranslator(const Jive::Syntax::Grammar &G) :
        Jive::Analyzer(G),
        stack(),
        charge(0),
        html(false)
        {
            //verbose = true;

            Y_Push(Name);
            Y_Push(Coef);

            push('+', *this, & FormulaTranslator::onPlus);
            push('-', *this, & FormulaTranslator::onMinus);


            Y_Func(Mult);
            Y_Func(Body);
            Y_Func(Formula);
            Y_Func(Z);


        }

        const char Weasel:: FormulaTranslator:: SubInit[] = "<sub>";
        const char Weasel:: FormulaTranslator:: SubQuit[] = "</sub>";


        const char Weasel:: FormulaTranslator:: SupInit[] = "<sup>";
        const char Weasel:: FormulaTranslator:: SupQuit[] = "</sup>";

        Weasel:: FormulaTranslator:: ~FormulaTranslator() noexcept
        {

        }

        String  Weasel:: FormulaTranslator:: decode(const Formula &f,
                                                    int * const    z,
                                                    const bool     toHtml)
        {
            html = toHtml;
            walk( & *f.code );
            if(z) *z = charge;
            return stack.pullTail();
        }

        void Weasel:: FormulaTranslator:: init()
        {
            stack.free();
            charge = 0;
        }


        void Weasel:: FormulaTranslator:: quit()
        {
            if(1!=stack.size()) throw Specific::Exception(grammar.lang->c_str(),"corrupted AST");
        }

        void Weasel:: FormulaTranslator:: show(const size_t depth) const
        {
            if(verbose) Core::Indent(std::cerr << "stack=",depth << 1) << stack << " / charge=" << charge << std::endl;
        }

        void Weasel:: FormulaTranslator:: onName(const Token &token)
        {
            stack << token.toString();
        }

        void Weasel:: FormulaTranslator:: onPlus(const Token &)
        {
            charge = 1;
        }

        void Weasel:: FormulaTranslator:: onMinus(const Token &)
        {
            charge = -1;
        }



        void Weasel:: FormulaTranslator:: onCoef(const Token &token)
        {
            const apn cf = token.toNatural();
            if(cf.bits()<=0) throw Specific::Exception(grammar.lang->c_str(),"null coefficient");
            stack << token.toString();
        }

        void Weasel:: FormulaTranslator:: onMult(const size_t)
        {
            assert( stack.size() >= 2);
            const String cof = stack.pullTail();
            const String grp = stack.pullTail();
            if(html)
            {
                stack << grp + SubInit + cof + SubQuit;
            }
            else
                stack << grp+cof;

        }

        void Weasel:: FormulaTranslator:: onBody(size_t n)
        {
            assert(stack.size()>=n);
            String res;
            while(n-- > 0) res >> stack.pullTail();
            if(stack.size()>0) res = '(' + res + ')';
            stack << res;
        }

        static inline
        String chargeToString(const int charge)
        {
            assert(0!=charge);

            String res;
            if(charge<0)
            {
                if(charge < -1) res += Decimal(-charge).c_str();
                res += '-';
            }
            else
            {
                if(charge>1) res += Decimal(charge).c_str();
                res += '+';
            }
            return res;
        }

        void Weasel:: FormulaTranslator:: onZ(const size_t n)
        {
            switch(n)
            {
                case 1:
                    break;

                case 2: {
                    assert(stack.size()>0);
                    const String s = stack.pullTail();
                    charge *= ASCII::Convert::To<int>(s,"species charge");
                } break;


                default:
                    throw Specific::Exception(grammar.lang->c_str(),"invalid Z/%s", Decimal(n).c_str());
            }

            if(0==charge) throw Specific::Exception(grammar.lang->c_str(),"corrupted charge computation");


            String      &tgt = stack.tail();
            const String xp  = chargeToString(charge);
            if(html)
            {
                tgt += SupInit;
                tgt += xp;
                tgt += SupQuit;
            }
            else
            {
                tgt += '^';
                tgt += xp;
            }


        }

        void Weasel:: FormulaTranslator:: onFormula(size_t)
        {
            
        }


        String Formula:: text(int *const z) const
        {
            static Weasel &weasel = Weasel::Instance();
            return weasel.formulaToText(*this,z);
        }

        String Formula:: html() const
        {
            static Weasel &weasel = Weasel::Instance();
            return weasel.formulaToHTML(*this);
        }


    }

}
