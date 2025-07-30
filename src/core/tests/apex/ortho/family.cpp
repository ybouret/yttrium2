

#include "y/ortho/family.hpp"
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
        const Ortho::Metrics metrics(dims);
        Ortho::Vector::Pool  vpool(metrics);
        Ortho::Family        F(vpool);
        CxxArray<int>        v(dims);

        while(F.quality !=  Ortho::Basis)
        {
            MakeRan(ran,v);
            if(Ortho::Vector * ortho = F.accepts(v))
                F.progeny(ortho);
            std::cerr << F << std::endl;
        }

        F.free();
        if(dims<=1) continue;

        std::cerr << std::endl;
        while( F.quality !=  Ortho::HyperPlane )
        {
            MakeRan(ran,v);
            if( Ortho::Vector * ortho = F.accepts(v))
                F.progeny(ortho);
        }
        std::cerr << F << std::endl;

        // find another vector
        AutoPtr<Ortho::Vector>  first = 0;
        do
            MakeRan(ran,v);
        while( (first = F.accepts(v)).isEmpty() );

        std::cerr << "first=" << first << std::endl;



        for(size_t iter=0;iter<4;++iter)
        {
            AutoPtr<Ortho::Vector> second = 0;
            do
            {
                MakeRan(ran,v);
            } while( (second=F.accepts(v)).isEmpty() );
            Y_ASSERT( *second == *first );
        }


        Ortho::Family::Pool fpool(vpool);
        Ortho::Family      *G = 0;
        do
        {
            MakeRan(ran,v);
        } while(0 == (G=F.newFamilyWith(v,fpool)));

        fpool.store(G);





    }


}
Y_UDONE()



