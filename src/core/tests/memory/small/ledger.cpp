

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


    Memory::Object::Ledger & ledger = Memory::Object::Ledger::Instance();
    std::cerr << "ready for " << ledger.callSign() << std::endl;

    for(size_t i=10+ran.leq(10);i>0;--i)
    {
        ledger.cache( unsigned(Memory::Object::Ledger::MinPageShift + ran.leq(Memory::Object::Ledger::NumPageShift/5)), ran.leq(5));
    }

    ledger.display(std::cerr,0);

    ledger.gc(100);
    
    ledger.display(std::cerr,0);


    Y_PRINTV(  Memory::Object::Ledger::MinPageShift );
    Y_PRINTV(  Memory::Object::Ledger::MaxPageShift );


}
Y_UDONE()
