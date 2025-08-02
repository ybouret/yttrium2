
#include "y/jive/source.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(source)
{
    if(argc>1)
    {
        Source source( Module::OpenFile(argv[1]) );
        Token  token;
        while(Char *ch=source.query())
        {
            token.pushTail(ch);
        }

        std::cerr << token << std::endl;

    }
}
Y_UDONE()
