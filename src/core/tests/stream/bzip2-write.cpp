
#include "y/stream/bzip2/output.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(stream_bzip2_write)
{
    BZip2::OutputFile fp("written.bz2");
    fp << "Hello, World!\n";

}
Y_UDONE()

