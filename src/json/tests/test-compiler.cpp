
#include "y/json/compiler.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(compiler)
{
    JSON::Compiler json;
    if( argc > 1 )
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        json( source );
    }
}
Y_UDONE()


