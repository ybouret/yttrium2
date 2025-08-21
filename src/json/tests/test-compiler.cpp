
#include "y/json/compiler.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(compiler)
{
    JSON::Compiler json;
    if( argc > 1 )
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        AutoPtr<Jive::XNode> tree = json.parse(source);
        Y_ASSERT(tree.isValid());
        Vizible::Render("jtree.dot", *tree);
    }
}
Y_UDONE()


