

#include "y/apex/api/ortho/family.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/pointer/auto.hpp"
using namespace Yttrium;


template <typename ARRAY>
static inline void MakeRan( Random::Bits &ran, ARRAY &v )
{
    for(size_t i=v.size();i>0;--i) v[i] = ran.in<int>(-5,5);
}

Y_UTEST(apex_ortho_family)
{

    Random::MT19937 ran;

    for(size_t dims=1;dims<=8;++dims)
    {
        std::cerr << std::endl << "--- dims=" << dims << std::endl;
        const Apex::Ortho::Metrics metrics(dims);
        Apex::Ortho::VCache        vcache = new Apex::Ortho::Vector::Cache(metrics);
        Apex::Ortho::Family        F(vcache);
        CxxArray<int>              v(dims);

        while(F.quality != Apex::Ortho::Basis)
        {
            MakeRan(ran,v);
            if(Apex::Ortho::Vector * ortho = F.accepts(v))
                F.progeny(ortho);
            std::cerr << F << std::endl;
        }

        F.free();
        if(dims<=1) continue;

        std::cerr << std::endl;
        while( F.quality != Apex::Ortho::HyperPlane )
        {
            MakeRan(ran,v);
            if(Apex::Ortho::Vector * ortho = F.accepts(v))
                F.progeny(ortho);
        }
        std::cerr << F << std::endl;

        // find another vector
        AutoPtr<Apex::Ortho::Vector>  first = 0;
        do
            MakeRan(ran,v);
        while( (first = F.accepts(v)).isEmpty() );

        std::cerr << "first=" << first << std::endl;



        for(size_t iter=0;iter<4;++iter)
        {
            AutoPtr<Apex::Ortho::Vector> second = 0;
            do
            {
                MakeRan(ran,v);
            } while( (second=F.accepts(v)).isEmpty() );
            Y_ASSERT( *second == *first );
        }


        {
            Apex::Ortho::FCache fc = new Apex::Ortho::Family::Cache(vcache);
        }





    }


}
Y_UDONE()



