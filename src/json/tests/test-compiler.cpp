
#include "y/json/compiler.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(compiler)
{
    JSON::Compiler json;
    JSON::Value    value;
    if( argc > 1 )
    {
        Jive::Source source( Jive::Module::OpenFile(argv[1]) );
        json( value, source );
    }
}
Y_UDONE()


