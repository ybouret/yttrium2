#include "y/random/park-miller.hpp"
#include "y/system/seed.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


namespace {

    template <typename T>
    static inline void RStats(Random::Bits &ran, const size_t n)
    {
        Vector<T> data(WithAtLeast,n);

        for(size_t i=0;i<n;++i)
            data << ran.toR<T>();

        T sum = 0;
        for(size_t i=1;i<=n;++i)
        {
            sum += data[i];
        }
        const T ave = sum/n;
        std::cerr << "ave=" << ave << std::endl;
        T sig = 0;
        for(size_t i=1;i<=n;++i)
        {
            const T del = data[i] -  ave;
            sig += del*del;
        }
        sig = sqrt(sig/n);
        std::cerr << "sig=" << sig << std::endl;
    }



}

Y_UTEST(random_bits)
{
    for(size_t i=0;i<8;++i)
    {
        std::cerr << "Seed: " << System::Seed::Get<uint16_t>() << std::endl;
    }

    Random::ParkMiller ran;
    for(size_t i=0;i<10;++i)
    {
        std::cerr << Hexadecimal( ran.next32() ) << std::endl;
    }

    size_t n = 1000;
    RStats<float>(ran,n);
    RStats<float>(ran,n);
    RStats<long double>(ran,n);



}
Y_UDONE()

