#include "y/random/isaac.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/park-miller.hpp"
#include "y/system/seed.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"
#include "y/container/sequence/vector.hpp"
#include <cmath>
#include "y/calculus/bits-for.hpp"

using namespace Yttrium;


namespace {

    template <typename T>
    static inline void RStats(Random::Bits &ran, const size_t n)
    {
        std::cerr << "RStats" << sizeof(T) * 8 << std::endl;
        Vector<T> data(WithAtLeast,n);

        for(size_t i=0;i<n;++i)
            data << ran.toR<T>();

        T sum = 0;
        for(size_t i=1;i<=n;++i)
        {
            sum += data[i];
        }
        const T ave = sum/n;
        std::cerr << "\tave=" << ave << std::endl;
        T sig = 0;
        for(size_t i=1;i<=n;++i)
        {
            const T del = data[i] -  ave;
            sig += del*del;
        }
        sig = sqrt(sig/n);
        std::cerr << "\tsig=" << sig << std::endl;
    }


    template <typename T>
    static inline void UStats(Random::Bits &ran, const size_t n)
    {
        std::cerr << "UStats" << sizeof(T) * 8 << std::endl;
        Vector<T> data(WithAtLeast,n);

        for(size_t i=0;i<n;++i)
            data << ran.toU<T>();

        long double sum = 0;
        for(size_t i=1;i<=n;++i)
        {
            sum += data[i];
        }
        const long double ave = sum/n;
        std::cerr << "\tave=" << ave << std::endl;
        long double sig = 0;
        for(size_t i=1;i<=n;++i)
        {
            const long double del = (long double)data[i] -  ave;
            sig += del*del;
        }
        sig = sqrt(sig/n);
        std::cerr << "\tsig=" << sig << std::endl;
    }


    template <typename T>
    static inline void SStats(Random::Bits &ran, const size_t n)
    {
        std::cerr << "SStats" << sizeof(T) * 8 << std::endl;
        Vector<T> data(WithAtLeast,n);

        for(size_t i=0;i<n;++i)
            data << ran.toS<T>();

        long double sum = 0;
        for(size_t i=1;i<=n;++i)
        {
            sum += data[i];
        }
        const long double ave = sum/n;
        std::cerr << "\tave=" << ave << std::endl;
        long double sig = 0;
        for(size_t i=1;i<=n;++i)
        {
            const long double del = (long double)data[i] -  ave;
            sig += del*del;
        }
        sig = sqrt(sig/n);
        std::cerr << "\tsig=" << sig << std::endl;
    }




    static inline void Stats(Random::Bits &ran, const size_t n)
    {
        std::cerr << std::endl;
        std::cerr << ran.callSign() << std::endl;
        RStats<float>(ran,n);
        RStats<double>(ran,n);
        RStats<long double>(ran,n);

        UStats<uint8_t>(ran,n);
        UStats<uint16_t>(ran,n);
        UStats<uint32_t>(ran,n);

        SStats<int8_t>(ran,n);
        SStats<int16_t>(ran,n);
        SStats<int32_t>(ran,n);

        for(size_t nbit=0;nbit<=64;++nbit)
        {
            for(size_t i=0;i<100;++i)
            {
                const uint64_t u = ran.to<uint64_t>(nbit);
                Y_ASSERT( BitsFor(u) == nbit );
            }
        }

        for(size_t i=0;i<10;++i)
        {
            std::cerr << ran.leq(10) << std::endl;
        }

    }
}

Y_UTEST(random_bits)
{
    for(size_t i=0;i<8;++i)
    {
        std::cerr << "Seed: " << System::Seed::Get<uint16_t>() << std::endl;
    }

    Random::ParkMiller ranParkMiller;
    Random::MT19937    ranMT19937;
    Random::ISAAC<4>   ranISAAC4;
    Random::ISAAC<8>   ranISAAC8;

    Random::Bits * ran[] = { & ranParkMiller, & ranMT19937, & ranISAAC4, & ranISAAC8 };
    size_t n = 1000;
    for(size_t i=0;i<sizeof(ran)/sizeof(ran[0]);++i)
    {
        Stats(*ran[i],n);
    }




}
Y_UDONE()

