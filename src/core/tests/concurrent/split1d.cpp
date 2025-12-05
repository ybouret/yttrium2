#include "y/concurrent/split/1d.hpp"
#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"
#include "y/type/ints.hpp"


namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            template <typename T>
            class Segment
            {
            public:
                static const T One = 1;
                Y_Args_Expose(T,Type);

                inline Segment(const Member &member,
                               const T       extent,
                               const T       iFirst) noexcept :
                offset(0),
                length( member.part(extent, Coerce(offset) ) ),
                utmost(0)
                {
                    Coerce(offset) += iFirst;
                    Coerce(utmost)  = offset + length - One;
                }

                inline Segment(const Segment &s) noexcept :
                offset(s.offset),
                length(s.length),
                utmost(s.utmost)
                {
                }

                inline virtual ~Segment() noexcept
                {

                }



                const T offset;
                const T length;
                const T utmost;

            private:
                Y_Disable_Assign(Segment);
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
            Concurrent::Member                    member(nproc,i-1);
            Concurrent::Divide::Segment<uint16_t> segment(member,length,1);
            std::cerr << "\t@" << member << ": " << segment.offset << " +" << segment.length << " -> " << segment.utmost << std::endl;
            sum += segment.length;
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
