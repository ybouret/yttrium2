

#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/equilibrium/db.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(solve1d)
{
    if(false)
    {
        for(size_t i=0;i<EDB::Count;++i)
        {
            std::cerr << EDB::Table[i] << std::endl;
        }
    }
    
    Weasel &   weasel = Weasel::Instance();
    Library    lib;
    Equilibria eqs;

    for(int i=1;i<argc;++i)
    {
        const String data = argv[i];
        weasel( Jive::Module::OpenData(data,data), lib, eqs);
    }

    std::cerr << "lib=" << lib << std::endl;
    std::cerr << "eqs=" << eqs << std::endl;

}
Y_UDONE()
