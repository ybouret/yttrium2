
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/opt/minimize.hpp"
#include "y/mkl/api/almost-equal.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        using namespace MKL;

        void Solver:: optimize(XMLog &xml, Prospect &pro, const xreal_t Fsub)
        {
            static const size_t MaxIter = ceil( -log( Numeric<real_t>::EPSILON) / log(2.0) );
            const xreal_t Fend = pro.a0 = affinity(pro.cc,SubLevel);
            Cend.ld(pro.cc);
            Solver & F = *this;
            XTriplet x = { zero, 0, one  };
            XTriplet f = { Fsub, 0, Fend };

            {
                const String fn = pro.eq.name + ".dat";
                OutputFile   fp(fn);
                const unsigned np = 200;
                for(unsigned i=0;i<=np;++i)
                {
                    const double u = i / (double(np));
                    fp("%.15g %s\n", u, F(u).str().c_str());
                }
            }

            // set a to minimum
            if(f.a>f.c) { Swap(f.a,f.c); Swap(x.a,x.c); }
            assert(f.a<=f.c);

            std::cerr << "MaxIter=" << MaxIter << std::endl;

            for(size_t iter=1;iter<=MaxIter;++iter)
            {
                assert(f.a<=f.c);
                f.b = F(x.b=x.middle()); assert( x.isOrdered() );
                std::cerr << "iter=" << iter << " " << x << " -> " << f << std::endl;
                if(f.b <= f.a )
                {
                    assert(f.isLocalMinimum());
                    goto OPTIMIZE;
                }
                assert(f.b>f.a);
                x.c = x.b;
                f.c = f.b;
                if( AlmostEqual<xreal_t>::Are(f.a,f.b) )
                    break;
            }

            std::cerr << "Global Min@" << x.a << std::endl;
            exit(0);

        OPTIMIZE:
            exit(0);
        }
    }

}


