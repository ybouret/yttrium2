

#include "y/jive/tag.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(tag)
{
    const Tag original = "Hello";
    std::cerr << original << std::endl;
    {
        OutputFile fp("tag.bin");
        (void)original.serialize(fp);
    }

    {
        InputFile fp("tag.bin");
        const Tag reloaded(fp);
        std::cerr << reloaded << std::endl;
        Y_CHECK(*reloaded==*original);
    }



}
Y_UDONE()
