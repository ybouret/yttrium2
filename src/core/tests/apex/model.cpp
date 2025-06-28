#include "y/apex/m/format.hpp"
#include "y/apex/block/model.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;



Y_UTEST(apex_model)
{
    System::Rand ran;

    {
        const uint64_t u = ran.gen<uint64_t>(57);
        std::cerr << Hexadecimal(u) << std::endl;
        {
            uint64_t q = u;
            size_t   s = 0;
            const uint8_t * const p = Apex::UFormatAs<uint8_t>(q,s);
            Hexadecimal::Display(std::cerr,p,s) << "#" << s << std::endl;
        }

        {
            uint64_t q = u;
            size_t   s = 0;
            const uint16_t * const p = Apex::UFormatAs<uint16_t>(q,s);
            Hexadecimal::Display(std::cerr,p,s) << "#" << s << std::endl;
        }

        {
            uint64_t q = u;
            size_t   s = 0;
            const uint32_t * const p = Apex::UFormatAs<uint32_t>(q,s);
            Hexadecimal::Display(std::cerr,p,s) << "#" << s << std::endl;
        }


    }

    {
        std::cerr << "Using Models" << std::endl;
        const uint64_t arr[2] = { ran.gen<uint64_t>( unsigned(ran.leq(30)) ), ran.gen<uint64_t>( unsigned(ran.leq(30)) ) };
        Apex::Model m(arr,2);
        
        std::cerr << m << std::endl;

        m.set(Apex::View8);
        std::cerr << m << std::endl;

        m.set(Apex::View16);
        std::cerr << m << std::endl;

        m.set(Apex::View32);
        std::cerr << m << std::endl;


    }
}
Y_UDONE()
