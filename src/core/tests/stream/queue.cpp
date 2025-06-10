



#include "y/stream/queue.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    static inline
    void checkIO(StreamQueue &Q, const uint64_t w64)
    {
        Q.release();
        const size_t nw = Q.encode64(w64);
        Y_ASSERT(Q->size==nw);
        uint64_t r64 = 0;
        Q.decode64(r64);
    }
}


Y_UTEST(stream_queue)
{
    System::Rand ran;
    StreamQueue  Q;


    for(unsigned n=0;n<=64;++n)
    {
        std::cerr << n << "/";
        for(size_t iter=0;iter<1000;++iter)
        {
            const uint64_t w64 = ran.gen<uint64_t>(n);
            checkIO(Q,w64);
        }
    }
    std::cerr << std::endl;
    checkIO(Q,IntegerFor<uint64_t>::Maximum);
}
Y_UDONE()
