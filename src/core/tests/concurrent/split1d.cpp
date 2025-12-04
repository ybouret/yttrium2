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
            class Cargo
            {
            public:

                Cargo(T            load,
                      const size_t size,
                      const size_t indx) :
                length(0),
                travel(0)
                {
                    {
                        size_t n = size;
                        for(size_t i=indx;i>0;--i)
                        {
                            Coerce(travel) += length;
                            Coerce(length)  = load / n--;
                            load -= length;
                        }
                    }
                }

                virtual ~Cargo() noexcept {}

                Cargo(const Cargo &cr) noexcept :
                length(cr.length),
                travel(cr.travel)
                {
                }

                const T length;
                const T travel;

            private:
                Y_Disable_Assign(Cargo);
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
        uint16_t sum = 0;
        for(size_t i=1;i<=nproc;++i)
        {
            Concurrent::Divide::Cargo<uint16_t> cr(length,nproc,i);
            std::cerr << "\t@travel=" << cr.travel << ": length=" << cr.length << std::endl;
            sum += cr.length;
        }
        Y_ASSERT(length == sum);
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
