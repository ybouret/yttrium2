

#include "y/string.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"


using namespace Yttrium;

namespace Yttrium
{

    
}

Y_UTEST(string)
{

    { String s; std::cerr << s << std::endl; }
    { String s = "a"; std::cerr << s << std::endl; }
    { String s = 'a'; std::cerr << s << std::endl; }
    {
        String s = "first";
        s += " second";
        std::cerr << s << std::endl;
    }

    {
        String source = "Hello, World!";
        const char * const fileName = "string.dat";
        size_t nw = 0;
        {
            OutputFile fp(fileName);
            nw = source.serialize(fp);
        }
        std::cerr << "Written=" << nw << std::endl;
        {
            InputFile fp(fileName);
            String    target(fp,"target");
            std::cerr << target << std::endl;
            Y_CHECK( target == source );
        }
    }



}
Y_UDONE()

