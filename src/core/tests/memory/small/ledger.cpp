

#include "y/memory/small/ledger.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{

}

Y_UTEST(memory_small_ledger)
{
    Concurrent::Singulet::Verbose = true;
    System::Rand  ran;


    Memory::Small::Ledger & ledger = Memory::Small::Ledger::Instance();
    std::cerr << "ready for " << ledger.callSign() << std::endl;

    for(size_t i=10+ran.leq(10);i>0;--i)
    {
        ledger.cache( unsigned(Memory::Small::Ledger::MinPageShift + ran.leq(Memory::Small::Ledger::NumPageShift/5)), ran.leq(5));
    }

    ledger.display(std::cerr,0);

    ledger.gc(100);
    
    ledger.display(std::cerr,0);


    Y_PRINTV(  Memory::Small::Ledger::MinPageShift );
    Y_PRINTV(  Memory::Small::Ledger::MaxPageShift );


}
Y_UDONE()
