
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
    for(size_t bits=1;bits<=1024;bits<<=1)
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

    const size_t     cols = 12;
    const size_t     rows = Apex::Ops32_64+1;

    CxxArray<size_t>    nbits(cols);
    Matrix<long double> rates(rows,cols);
    for(size_t bits=2,i=1;i<=nbits.size();++i, bits <<= 1)
    {
        nbits[i] = bits;
    }
    std::cerr << "bits=" << nbits << std::endl;

    for(int j=0;j<=Apex::Ops32_64;++j)
    {
        Apex::Natural::Ops = Apex::OpsMode(j);
        uint64_t tmx = 0;
        const Temporary<uint64_t *> temp(Apex::Device::ProbeMUL,&tmx);
        Y_ASSERT(&tmx == Apex::Device::ProbeMUL);

        std::cerr << " " << apn::HumanReadableOps();
        for(size_t i=1;i<=rows;++i)
        {
            const size_t bits = nbits[i];
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
            while( ell < 0.005 );
            const long double rate = cycles / ell;
            rates[i][j+1] = rate;
        }
    }
    std::cerr << std::endl;


    std::cerr << "--------" << std::endl;
    for(int j=0;j<=Apex::Ops32_64;++j)
    {
        Apex::Natural::Ops = Apex::OpsMode(j);
        std::cerr << std::setw(8) << apn::HumanReadableOps() << ' ';
        const size_t icol = j+1;
        long double  rmax = rates[1][icol];
        size_t       imax = 1;
        for(size_t i=2;i<=rows;++i)
        {
            const long double rtmp = rates[i][icol];
            if(rtmp>rmax)
            {
                rmax = rtmp;
                imax = i;
            }
        }


        for(size_t i=1;i<=rows;++i)
        {
            std::cerr << HumanReadable( rates[i][j+1] ) << (i==imax ? "* " : "  ");
        }
        std::cerr << std::endl;
    }






}
Y_UDONE()
