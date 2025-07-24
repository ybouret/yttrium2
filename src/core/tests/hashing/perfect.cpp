

#include "y/hashing/perfect.hpp"
#include "y/utest/run.hpp"

#include "y/string.hpp"
#include "y/stream/libc/input.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/graphviz/vizible.hpp"

using namespace Yttrium;

Y_UTEST(hashing_perfect)
{
    const char msg[] = "Hello World!";

    Hashing::Perfect mph;
    const Hashing::Perfect &cmph = mph;
    int k = 0;

    mph.at(msg,++k);

    Y_ASSERT(k==mph(msg));
    Y_ASSERT(k==cmph(msg));

    if(argc>1)
    {
        Vector<String> path;
        {
            InputFile fp(argv[1]);
            String    line;
            while(fp.gets(line))
            {
                path << line;
                mph.at(line,++k);
            }
        }
    }

    Vizible::Render("mph.dot",mph);



}
Y_UDONE()

