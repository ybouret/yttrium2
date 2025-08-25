#include "y/jive/dsl/chemical-formula.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

namespace
{
    class Formulas : public Parser
    {
    public:
        inline explicit Formulas() : Parser("Formulas")
        {
            Agg & self = agg(lang);
            (void) term("COEFF","[:digit:]+");

            const Rule & BLANK = mark( "[:blank:]");
            const Rule & ENDL  = markNL("[:endl:]");
            const Rule & WHITE = (alt("WHITE") << BLANK << ENDL);
            const Rule & SPACE = opt("SPACE",WHITE);
            ChemicalFormula f("Formula");
            const Rule & FORMULA = f.install(*this);

            Alt & STATEMENT = alt("Statement");

            STATEMENT << cat(SPACE,FORMULA);
            STATEMENT << WHITE;
            self << zom(STATEMENT);
            render();
        }


        inline virtual ~Formulas() noexcept
        {

        }

    private:
        Y_Disable_Copy_And_Assign(Formulas);
    };
}

Y_UTEST(formula)
{
    Formulas p;

    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]));
        AutoPtr<XNode> tree = p.parse(source); Y_ASSERT(tree.isValid());
        Vizible::Render("formula.dot",*tree);
    }


}
Y_UDONE()

