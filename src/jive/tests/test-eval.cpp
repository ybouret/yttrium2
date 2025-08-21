
#include "y/jive/parser.hpp"
#include "y/utest/run.hpp"

#include "y/jive/lexical/comment/single-line.hpp"

#include "y/string/env.hpp"

#include "y/jive/analyzer.hpp"

using namespace Yttrium;


namespace
{
    class Eval : public Jive::Parser
    {
    public:
        inline explicit Eval() : Jive::Parser("Eval")
        {
            drop("[:blank:]");
            endl("[:endl:]",false);
            comment("comment","//");


            Agg & addOp = act("addOp");
            Agg & mulOp = act("mulOp");
            Agg & powOp = act("powOp");
            Alt & atom  = alt("atom");
            atom << term("ID","[:alpha:][:word:]*") << term("INT","[:digit:]+") << parens(addOp);

            powOp << atom << bonus('^',powOp);


            const Rule & MUL   = term('*');
            const Rule & DIV   = term('/');
            mulOp << powOp << zom( cat(pick(MUL,DIV),powOp) );


            const Rule & PLUS  = term('+');
            const Rule & MINUS = term('-');
            addOp << mulOp << zom( cat(pick(PLUS,MINUS),mulOp) );

            render();
            validate();

        }

        inline virtual ~Eval() noexcept
        {
            
        }

    private:
        Y_Disable_Copy_And_Assign(Eval);
    };

}

Y_UTEST(eval)
{
    Eval          eval;
    Jive::Walker  analyze(eval);
    if(argc>1)
    {
        Jive::Source         source( Jive::Module::OpenFile(argv[1]) );
        AutoPtr<Jive::XNode> tree = eval.parse(source);
        Y_ASSERT(tree.isValid());
        Vizible::Render("eval-tree.dot",*tree);

        analyze.walk( & *tree );

    }

}
Y_UDONE()
