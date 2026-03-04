#include "y/system/program.hpp"
#include "y/chemical/plexus/clusters.hpp"
#include "y/chemical/weasel.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_PROGRAM()
{
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

    std::cerr << "Rendering..." << std::endl;
    cls.viz("cs");

}
Y_EXECUTE()

