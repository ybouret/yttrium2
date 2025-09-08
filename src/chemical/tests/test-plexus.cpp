


#include "y/chemical/weasel.hpp"
#include "y/chemical/plexus/clusters.hpp"
#include "y/chemical/plexus/steady-state.hpp"

#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/string/env.hpp"
#include "y/ascii/convert.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace Chemical;



Y_UTEST(plexus)
{
    //MKL::BracketVerbose = true;

    Random::MT19937 ran;
    real_t          probaZero = 0;
    {
        String pzs;
        if( Environment::Get(pzs, "probaZero") )
        {
            probaZero = ASCII::Convert::To<real_t>(pzs,"probaZero");
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

    bool verbose = true;
    XMLog xml(std::cerr,verbose);

    Clusters cls(xml,eqs,0.0);

    for(const Cluster *cl=cls->head;cl;cl=cl->next)
    {
        std::cerr << *cl << std::endl;
    }

    const size_t M = lib->size();
    XArray       C0(M,0);
    lib.conc(ran,C0,probaZero);

    lib.print(std::cerr, "[", C0, "]", xreal_t::ToString);

    SteadyState s3(cls);

    s3.solve(xml,C0);


    lib.print(std::cerr, "[", C0, "]", xreal_t::ToString);


    {
        OutputFile fp("cs.dot");
        Vizible::Enter(fp);
        for(const Cluster *cl=cls->head;cl;cl=cl->next)
        {
            cl->viz(fp,1);
        }

        Vizible::Leave(fp);
    }

    Vizible::DotToPng("cs.dot");


}
Y_UDONE()
