


#include "y/chemical/weasel.hpp"
#include "y/chemical/plexus/clusters.hpp"

#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;
using namespace Chemical;



Y_UTEST(plexus)
{
    Random::MT19937 ran;


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

    Clusters cls(xml,eqs);

    for(const Cluster *cl=cls->head;cl;cl=cl->next)
    {
        std::cerr << *cl << std::endl;
    }

}
Y_UDONE()
