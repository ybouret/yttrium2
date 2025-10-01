#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel & weasel = Weasel::Instance();

    std::cerr << weasel.callSign() << std::endl;

    Library lib;
    Lua::VM lvm = new Lua::State();

    if(argc>1)
    {
        AutoPtr<XNode> tree = weasel.parse( Jive::Module::OpenFile(argv[1]) );
        Y_ASSERT( tree.isValid() );
        Vizible::Render("wtree.dot", *tree);

        Y_ASSERT( tree->name() == Weasel::CallSign );
        const XTree &top = dynamic_cast<const XTree&>(*tree);

        {
            OutputFile fp("species.dot");
            Vizible::Enter(fp);

            unsigned  indx = 1;
            for(const XNode *node = top.head; node;node=node->next, ++indx)
            {
                std::cerr << "found " << node->name() << std::endl;
                if(node->defines<Formula>())
                {
                    const Formula formula = node->clone();
                    int           charge  = 0;
                    const String  spname  = weasel.formulaToText(formula,&charge);
                    std::cerr << "species=" << spname << ", charge=" << charge << std::endl;
                    const String  sphtml = weasel.formulaToHTML(formula);
                    std::cerr << "html:  " << sphtml << std::endl;
                    const String  splatex = weasel.formulaToLaTeX(formula);
                    std::cerr << "latex: " << splatex << std::endl;


                    fp("%u[label=<",indx) << sphtml << ">];\n";

                    continue;
                }

                if(node->defines<Equilibrium>())
                {
                    AutoPtr<Equilibrium> eq = weasel.compile(node,lib,1,lvm);
                }
            }

            Vizible::Leave(fp);
        }

        Vizible::DotToPng("species.dot");



    }

}
Y_UDONE()
