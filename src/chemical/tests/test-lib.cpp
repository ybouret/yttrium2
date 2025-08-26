

#include "y/chemical/library.hpp"
#include "y/chemical/reactive/components.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Chemical;

Y_UTEST(library)
{

    Library lib;

    const Species &h  = lib["H^+"];
    const Species &w  = lib["HO^-"];
    const Species &AH = lib["AH"];
    const Species &Am = lib["A^-"];


    std::cerr << lib << std::endl;

    Actors ea(Actor::InEquilibrium);
    ea.add(h);    std::cerr << ea.name << std::endl;
    ea.add(2,w);  std::cerr << ea.name << std::endl;

    
    Actors ca(Actor::InConservation);
    ca.add(3,h);  std::cerr << ca.name << std::endl;
    ca.add(1,w);  std::cerr << ca.name << std::endl;

    Components water("water",1);
    water.p(h);
    water.p(w);
    std::cerr << water << std::endl;

    Components acetic("acetic",2);
    acetic.p(h);
    acetic.p(Am);
    acetic.r(AH);
    std::cerr << acetic << std::endl;

}
Y_UDONE()
