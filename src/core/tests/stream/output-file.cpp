


#include "y/stream/libc/output.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(stream_output_file)
{
    {
        OutputFile fp("output.dat");
        fp.write('y');
        fp.frame("hello",5);

        fp << '\n';
        fp << "World!";
        fp << '\n';
        fp("from %s, line=%d\n", program, __LINE__);

    }





}
Y_UDONE()
