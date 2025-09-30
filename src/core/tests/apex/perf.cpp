
#include "y/apex/natural.hpp"
#include "y/apex/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/system/wall-time.hpp"
#include "y/memory/stealth.hpp"
#include "y/format/human-readable.hpp"
#include "y/apex/k/device.hpp"
#include "y/type/temporary.hpp"

#include "y/container/cxx/array.hpp"
#include "y/container/matrix.hpp"


using namespace Yttrium;



Y_UTEST(apex_perf)
{
    Random::ParkMiller ran;
    const unsigned     cycle = 100;
    System::WallTime   chrono;

    std::cerr << "SHR" << std::endl;
    for(size_t bits=1;bits<=4096;bits<<=1)
    {

        uint64_t  tmx[Apex::Metrics::Plans];
        Y_Memory_BZero(tmx);

        for(unsigned j=0;j<cycle;++j)
        {
            const apn n(ran,bits);
            for(unsigned i=0;i<Apex::Metrics::Plans;++i)
            {
                apn p = n;
                Apex::Natural::BWO = Apex::PlanType(i);
                while(p.bits())
                {
                    Y_WallTime_Mark(&tmx[i]);
                    p.shr();
                    Y_WallTime_Gain(&tmx[i]);
                }
            }
        }

        for(unsigned i=0;i<Apex::Metrics::Plans;++i)
        {
            const long double speed = std::ceil((long double)cycle / chrono(tmx[i]));
            std::cerr << " " << HumanReadable( (uint64_t)speed ) << "/s";
        }
        std::cerr << std::endl;
    }

    std::cerr << std::endl;
    std::cerr << "Long Multiplication" << std::endl;

    const size_t     cols = 13;
    const size_t     rows = Apex::Ops32_64+1;

    CxxArray<size_t>    nbits(cols);
    Matrix<long double> rates(rows,cols);
    for(size_t bits=2,i=1;i<=nbits.size();++i, bits <<= 1)
    {
        nbits[i] = bits;
    }
    std::cerr << "bits=" << nbits << std::endl;

    for(unsigned i=1;i<=Apex::Ops32_64+1;++i)
    {
        Apex::Natural::Ops = Apex::OpsMode(i-1);
        uint64_t tmx = 0;
        const Temporary<uint64_t *> temp(Apex::Device::ProbeMUL,&tmx);
        Y_ASSERT(&tmx == Apex::Device::ProbeMUL);

        (std::cerr << " " << apn::HumanReadableOps()).flush();
        for(size_t j=1;j<=cols;++j)
        {
            const size_t bits = nbits[j];
            tmx = 0;
            uint64_t cycles = 0 ;
            long double ell = 0;
            do
            {
                ++cycles;
                const apn lhs(ran,bits);
                const apn rhs(ran,bits);
                const apn prod = lhs * rhs;
                ell = chrono(tmx);
                //(std::cerr << ell << "s    \r").flush();
            }
            while( cycles < 1000 && ell < 0.1 );
            const long double rate = (long double)cycles / ell;
            rates[i][j] = rate;
            (std::cerr << ' ' << bits << "/" << cycles).flush();

        }
        std::cerr << std::endl;
    }
    std::cerr << std::endl;



    std::cerr << "--------" << std::endl;

    CxxArray<size_t> maxi(cols);
    for(size_t j=1;j<=cols;++j)
    {
        long double  rmax = rates[1][j];
        size_t       imax = 1;
        for(size_t i=2;i<=rows;++i)
        {
            const long double rtmp = rates[i][j];
            if(rtmp>rmax)
            {
                rmax = rtmp;
                imax = i;
            }
        }
        maxi[j] = imax;
    }

    std::cerr << std::setw(8) << "/" << ' ';
    for(size_t j=1;j<=cols;++j)
    {
        std::cerr << std::setw(8) << nbits[j] << "  ";
    }
    std::cerr << std::endl;
    for(size_t i=1;i<=Apex::Ops32_64+1;++i)
    {
        Apex::Natural::Ops = Apex::OpsMode(i-1);
        std::cerr << std::setw(8) << apn::HumanReadableOps() << ' ';
        for(size_t j=1;j<=cols;++j)
        {
            std::cerr << HumanReadable( (uint64_t)rates[i][j] ) << (i==maxi[j] ? "* " : "  ");
        }
        std::cerr << std::endl;
    }


    apn::Set(Apex::FourierMultiplication);

    {
        uint64_t tmx = 0;
        const Temporary<uint64_t *> temp(Apex::Device::ProbeMUL,&tmx);
        Y_ASSERT(&tmx == Apex::Device::ProbeMUL);

        std::cerr << "Fourier" << std::endl;
        for(size_t j=1;j<=cols;++j)
        {
            const size_t bits = nbits[j];
            tmx = 0;
            uint64_t cycles = 0 ;
            long double ell = 0;
            do
            {
                ++cycles;
                const apn lhs(ran,bits);
                const apn rhs(ran,bits);
                const apn prod = lhs * rhs;
                ell = chrono(tmx);
                //(std::cerr << ell << "s    \r").flush();
            }
            while( cycles < 1000 && ell < 0.1 );
            const long double rate = (long double)cycles / ell;
            std::cerr << ' ' << HumanReadable( (uint64_t)rate ) << "/s @" << std::setw(6) << bits << " bits" << std::endl;
        }
        std::cerr << std::endl;
    }






}
Y_UDONE()
