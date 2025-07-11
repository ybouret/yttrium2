
#include "y/apex/natural.hpp"
#include "y/apex/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/system/wall-time.hpp"
#include "y/memory/stealth.hpp"
#include "y/format/human-readable.hpp"

using namespace Yttrium;



Y_UTEST(apex_perf)
{
    Random::ParkMiller ran;
    const unsigned     cycle = 100;
    System::WallTime   chrono;

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
            const double speed = ceil((long double)cycle / chrono(tmx[i]));
            std::cerr << " " << HumanReadable( speed ) << "/s";
        }
        std::cerr << std::endl;

    }

}
Y_UDONE()
