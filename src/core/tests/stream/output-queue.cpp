



#include "y/stream/output-queue.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"



using namespace Yttrium;

Y_UTEST(stream_output_queue)
{
    System::Rand ran;
    OutputQueue  Q;

    for(unsigned n=0;n<=64;++n)
    {
        Q.release();
        const uint64_t qw = ran.gen<uint64_t>(n);
        Q.encode64(qw);
    }

}
Y_UDONE()
