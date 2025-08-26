#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"
#include "y/jive/syntax/node/internal.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(weasel)
{
    Weasel & weasel = Weasel::Instance();

    std::cerr << weasel.callSign() << std::endl;

    if(argc>1)
    {
        AutoPtr<XNode> tree = weasel.parse( Jive::Module::OpenFile(argv[1]) );
        Y_ASSERT( tree.isValid() );
        Vizible::Render("wtree.dot", *tree);

        Y_ASSERT( tree->name() == Weasel::CallSign );
        const XTree &top = dynamic_cast<const XTree&>(*tree);

        for(const XNode *node = top.head; node;node=node->next)
        {
            std::cerr << "found " << node->name() << std::endl;
            if(node->defines<Formula>())
            {
                const Formula formula = node->clone();
                int           charge  = 0;
                const String  spname  = weasel.formulaToText(formula,&charge);
                std::cerr << "species=" << spname << ", charge=" << charge << std::endl;
            }
        }



    }

}
Y_UDONE()
