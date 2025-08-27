

#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/equilibrium/db.hpp"
#include "y/chemical/plexus/solve1d.hpp"

#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;
using namespace Chemical;



Y_UTEST(solve1d)
{
    Random::MT19937 ran;

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

    XArray C(lib->size(),0);
    

    XMul    xmul;
    Solve1D solve;

    for( Equilibria::Iterator it = eqs.begin(); it != eqs.end(); ++it)
    {
        Equilibrium &eq = **it;
        const xreal_t K = eq.K(0.0);
        lib.conc(ran,C);
        lib.print(std::cerr, "[", C, "]",xreal_t::ToString);
        std::cerr << "ma=" << eq.massAction(xmul, K, C, TopLevel).str() << std::endl;
        const XArray C0 = C;
        solve(eq,K,C,TopLevel,C0);

        lib.print(std::cerr, "[", C, "]",xreal_t::ToString);

    }




}
Y_UDONE()
