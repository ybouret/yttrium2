
#include "y/calculus/prime/next.hpp"

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/stream/libc/output.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

template <typename T> static inline
T Transform(const T &x)
{
    return x;
}

Y_UTEST(calculus_primes)
{

    uint32_t i    = 3;

    Vector<uint8_t> gap;
    while(true)
    {
        const uint32_t j   = Prime::Next(i+1);
        const uint32_t g   = j-i;    Y_ASSERT( 0 == (g&1)  );
        const uint32_t d   = (g>>1); Y_ASSERT(d<256);
        gap << d;
        i = j;
        if( j >= IntegerFor<uint16_t>::Maximum )
            break;
    }
    std::cerr << "#gap=" << gap.size() << std::endl;

    i = 3; Y_ASSERT(Prime::Test(i));
    for(size_t k=1;k<=gap.size();++k)
    {
        i += gap[k] << 1; std::cerr << i << std::endl;
        Y_ASSERT(Prime::Test(i));
    }


}
Y_UDONE()


#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/split/1d.hpp"

namespace
{
    class Computer
    {
    public:
        static const uint64_t One   = 1;
        static const uint64_t Lower = 2;
        //static const uint64_t Upper = One << 32;
        static const uint64_t Upper = 1023;
        static const uint64_t Delta = Upper-Lower+One;

        explicit Computer() noexcept
        {

        }

        virtual ~Computer() noexcept
        {

        }

        inline void find(const Concurrent::Context &ctx)
        {
            Concurrent::Split::In1D       in1d(Delta);
            const Concurrent::Split::Zone zone = in1d(ctx,Lower);
            { Y_Giant_Lock(); std::cerr << "@" << ctx << " : zone=" << zone << " -> "<< (zone.offset + zone.length - One) << std::endl; }
        }


    private:
        Y_Disable_Copy_And_Assign(Computer);
    };

    const uint64_t Computer::Lower;
    const uint64_t Computer::Upper;

}

Y_UTEST(calculus_fprimes)
{
    Concurrent::Crew crew( Concurrent::Site::Default );
    Computer         computer;
    std::cerr << Hexadecimal(Computer::Lower) << " -> " << Hexadecimal( Computer::Upper ) << std::endl;
    {
        Concurrent::Kernel kernel( &computer, & Computer::find);
        crew(kernel);
    }



}
Y_UDONE()
