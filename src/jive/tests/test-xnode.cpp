#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Jive;

Y_UTEST(xnode)
{
    Y_SIZEOF(Syntax::Node);
    Y_SIZEOF(Syntax::TerminalNode);
    Y_SIZEOF(Syntax::InternalNode);

}
Y_UDONE()

