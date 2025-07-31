
#include "y/stream/gzip/output.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

using namespace Yttrium;

Y_UTEST(stream_gzip_write)
{
    const String fileName = "foo.gz";

    {
        GZip::Output fp(fileName,9);
        fp << "Hello, World!\n";
    }


}
Y_UDONE()
