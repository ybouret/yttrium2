
#include "y/apex/block/model.hpp"



#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;



Y_UTEST(apex_model)
{
    System::Rand ran;


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
