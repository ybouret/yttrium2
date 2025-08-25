
#include "y/chemical/weasel/formula/to-text.hpp"
#include "y/format/decimal.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{

    namespace Chemical
    {

#define Y_Push(ID) Y_Jive_Push(FormulaToText,ID)
#define Y_Func(ID) Y_Jive_Func(FormulaToText,ID)

        Weasel:: FormulaToText:: FormulaToText(const Jive::Syntax::Grammar &G) :
        Jive::Analyzer(G),
        stack(),
        charge(0)
        {
            verbose = true;

            Y_Push(Name);
            Y_Push(COEF);

            push('+', *this, & FormulaToText::onPlus);
            push('-', *this, & FormulaToText::onMinus);


            Y_Func(Mult);
            Y_Func(Body);
            Y_Func(Formula);
            Y_Func(Z);


        }

        Weasel:: FormulaToText:: ~FormulaToText() noexcept
        {

        }

        String  Weasel:: FormulaToText:: compile(const Formula &f, int &z)
        {
            walk( & *f.code );
            z = charge;
            return stack.pullTail();
        }

        void Weasel:: FormulaToText:: init()
        {
            stack.free();
            charge = 0;
        }


        void Weasel:: FormulaToText:: quit()
        {
            if(1!=stack.size()) throw Specific::Exception(grammar.lang->c_str(),"corrupted AST");
        }

        void Weasel:: FormulaToText:: show(const size_t depth) const
        {
            if(verbose) Core::Indent(std::cerr << "stack=",depth << 1) << stack << " / charge=" << charge << std::endl;
        }

        void Weasel:: FormulaToText:: onName(const Token &token)
        {
            stack << token.toString();
        }

        void Weasel:: FormulaToText:: onPlus(const Token &)
        {
            charge = 1;
        }

        void Weasel:: FormulaToText:: onMinus(const Token &)
        {
            charge = -1;
        }



        void Weasel:: FormulaToText:: onCOEF(const Token &token)
        {
            // TODO: validate coeff ?
            const apn cf = token.toNatural();
            if(cf.bits()<=0) throw Specific::Exception(grammar.lang->c_str(),"null coefficient");
            stack << token.toString();
        }

        void Weasel:: FormulaToText:: onMult(const size_t)
        {
            assert( stack.size() >= 2);
            const String cof = stack.pullTail();
            const String grp = stack.pullTail();
            const String res = grp+cof;
            stack << res;
        }

        void Weasel:: FormulaToText:: onBody(size_t n)
        {
            assert(stack.size()>=n);
            String res;
            while(n-- > 0) res >> stack.pullTail();
            if(stack.size()>0) res = '(' + res + ')';
            stack << res;
        }

        void Weasel:: FormulaToText:: onZ(const size_t n)
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

        }

        void Weasel:: FormulaToText:: onFormula(size_t)
        {
            
        }


        String Formula:: text(int *const z) const
        {
            static Weasel &weasel = Weasel::Instance();
            return weasel.formulaToString(*this,z);
        }


    }

}
