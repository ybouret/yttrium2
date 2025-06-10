



#include "y/stream/queue.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"



using namespace Yttrium;

Y_UTEST(stream_queue)
{
    System::Rand ran;
    StreamQueue  Q;

    for(unsigned n=0;n<=64;++n)
    {
        std::cerr << "n=" << n << std::endl;
        Q.release();
        const uint64_t qw = ran.gen<uint64_t>(n);
        Q.encode64(qw);
    }

}
Y_UDONE()
