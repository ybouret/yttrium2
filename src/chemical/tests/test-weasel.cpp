#include "y/chemical/weasel.hpp"
#include "y/utest/run.hpp"

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
    }

}
Y_UDONE()
