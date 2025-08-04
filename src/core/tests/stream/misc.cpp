#include "y/stream/misc/sequence.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

Y_UTEST(stream_misc)
{

    {
        String str;
        {
            OutputSequence<String> fp(str);
            fp << "Hello!";
        }
        std::cerr << str << std::endl;
    }

    {
        Vector<char> vec;
        {
            OutputSequence< Vector<char> > fp(vec);
            fp << "Hello!";
        }
        std::cerr << vec << std::endl;
    }
}
Y_UDONE()
