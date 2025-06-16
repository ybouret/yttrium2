


#include "y/stream/libc/output.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(stream_output_file)
{
    {
        OutputFile fp("output.dat");
        fp.write('y');
        fp.frame("hello",5);
    }





}
Y_UDONE()
