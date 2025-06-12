



#include "y/stream/queue.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    static inline
    void checkIO(StreamQueue &Q, const uint64_t w64)
    {
#if 0
        Q.release();
        const size_t nw = Q.encode64(w64);
        Y_ASSERT(Q->size==nw);
        uint64_t r64 = 0;
        Q.decode64(r64);
#endif
    }
}


Y_UTEST(stream_queue)
{
    System::Rand ran;
    StreamQueue  Q;

#if 0
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

    std::cerr << "Check 8-bits" << std::endl;
    for(unsigned i=0;i<256;++i)
    {
        Q.release();
        const uint8_t b = uint8_t(i);
        Y_ASSERT(1==Q.emitCBR(b));
        uint8_t r = 0;
        Y_ASSERT(1==Q.readCBR(r));
        Y_ASSERT(r==b);
    }

    std::cerr << "Check 16-bits" << std::endl;
    for(unsigned i=0;i<65536;++i)
    {
        Q.release();
        const uint16_t w = uint8_t(i);
        Y_ASSERT(2==Q.emitCBR(w));
        uint16_t r = 0;
        Y_ASSERT(2==Q.readCBR(r));
        Y_ASSERT(r==w);
    }

    std::cerr << "Check 32-bits" << std::endl;
    for(unsigned i=0;i<=32;++i)
    {
        for(size_t iter=0;iter<1000;++iter)
        {
            Q.release();
            const uint32_t x = ran.gen<uint32_t>(i);
            Y_ASSERT(4==Q.emitCBR(x));
            uint32_t r = 0;
            Y_ASSERT(4==Q.readCBR(r));
            Y_ASSERT(r==x);
        }
    }

    std::cerr << "Check 64-bits" << std::endl;
    for(unsigned i=0;i<=64;++i)
    {
        for(size_t iter=0;iter<1000;++iter)
        {
            Q.release();
            const uint64_t x = ran.gen<uint64_t>(i);
            Y_ASSERT(8==Q.emitCBR(x));
            uint64_t r = 0;
            Y_ASSERT(8==Q.readCBR(r));
            Y_ASSERT(r==x);
        }
    }
#endif

}
Y_UDONE()
