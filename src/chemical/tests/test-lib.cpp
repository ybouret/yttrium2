

#include "y/chemical/library.hpp"
#include "y/chemical/reactive/actors.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(library)
{

    Library lib;

    const Species &h = lib["H^+"];
    const Species &w = lib["HO^-"];

    std::cerr << lib << std::endl;

    Actors ea(Actor::InEquilibrium);
    ea.add(h);    std::cerr << ea.name << std::endl;
    ea.add(2,w);  std::cerr << ea.name << std::endl;

    
    Actors ca(Actor::InConservation);
    ca.add(3,h);  std::cerr << ca.name << std::endl;
    ca.add(1,w);  std::cerr << ca.name << std::endl;
}
Y_UDONE()
