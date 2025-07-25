

#include "y/apex/api/ortho/family.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;

Y_UTEST(apex_ortho_family)
{

    Random::MT19937 ran;

    for(size_t dims=1;dims<=3;++dims)
    {
        std::cerr << std::endl << "--- dims=" << dims << std::endl;
        const Apex::Ortho::Metrics metrics(dims);
        Apex::Ortho::VCache        vcache = new Apex::Ortho::Vector::Cache(metrics);
        Apex::Ortho::Family        F(vcache);
        CxxArray<int>              v(dims);

        while(F.quality != Apex::Ortho::Basis)
        {
            for(size_t i=dims;i>0;--i) v[i] = ran.in<int>(-5,5);
            if(F.accepts(v))
                F.grow();
            std::cerr << F << std::endl;
        }




    }


}
Y_UDONE()



