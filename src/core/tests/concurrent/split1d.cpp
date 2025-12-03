#include "y/concurrent/split/1d.hpp"
#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"



namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {
            template <typename T>
            class Burden
            {
            public:

                Burden(const T      total,
                       const size_t size,
                       const size_t indx) :
                length(0),
                travel(0)
                {
                    T remain = total;
                    {
                        size_t n = size;
                        for(size_t i=indx;i>0;--i)
                        {
                            Coerce(travel) += length;
                            Coerce(length)  = remain / n--;
                            remain -= length;
                        }
                    }
                }

                virtual ~Burden() noexcept {}

                const T length;
                const T travel;

            private:
                Y_Disable_Copy_And_Assign(Burden);
            };
        }
    }
}

using namespace Yttrium;




Y_UTEST(concurrent_split1d)
{
    const uint16_t length = 8;
    const size_t   nmax   = 10;

    for(size_t nproc=1;nproc<=nmax;++nproc)
    {
        std::cerr << std::endl << "nproc=" << nproc << std::endl;
        for(size_t i=1;i<=nproc;++i)
        {
            Concurrent::Divide::Burden<uint16_t> burden(length,nproc,i);
            std::cerr << "\tlength=" << burden.length << ", travel=" << burden.travel << std::endl;
        }
    }
#if 0
    Concurrent::Split::In1D  in1d(length);

    for(size_t nproc=1;nproc<=nmax;++nproc)
    {
        std::cerr << std::endl << "nproc=" << nproc << std::endl;
        //Concurrent::Split::In1D_(segments,offset,length,nproc);
        in1d.boot(nproc,0);
        while( in1d.next() )
        {
            std::cerr << "\t" << in1d.offset << "+" << in1d.length << std::endl;
        }

        Concurrent::Split::Segments<int> segments(nproc);

        in1d(segments,-5);
        std::cerr << segments << std::endl;

    }
#endif

}
Y_UDONE()
