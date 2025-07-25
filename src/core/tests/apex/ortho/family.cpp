

#include "y/apex/api/ortho/family.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"

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
            if(F.accepts(v))
                F.grow();
            std::cerr << F << std::endl;
        }

        F.free();
        if(dims<=1) continue;

        std::cerr << std::endl;
        while( F.quality != Apex::Ortho::HyperPlane )
        {
            for(size_t i=dims;i>0;--i) v[i] = ran.in<int>(-5,5);
            if(F.accepts(v))
                F.grow();
        }
        std::cerr << F << std::endl;

        // find another vector
        do
        {
            MakeRan(ran,v);
        } while( !F.accepts(v) );

        const Apex::Ortho::Vector first = F.last();
        std::cerr << "first=" << first << std::endl;

        for(size_t iter=0;iter<4;++iter)
        {
            do
            {
                MakeRan(ran,v);
            } while( !F.accepts(v) );

            const Apex::Ortho::Vector other = F.last();
            Y_ASSERT(other==first);
        }


    }


}
Y_UDONE()



