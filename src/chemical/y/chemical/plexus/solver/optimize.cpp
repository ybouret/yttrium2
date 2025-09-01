
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        using namespace MKL;

        void Solver:: optimize(XMLog &xml, Prospect &pro)
        {
            static const size_t MaxIter = ceil( -log( Numeric<real_t>::EPSILON) / log(2.0) );


            //------------------------------------------------------------------
            //
            // compute RMS at solve1D result (ie at xi)
            //
            //------------------------------------------------------------------
            const char *       pos = Core::Unknown;
            const xreal_t      W1 = pro.W1 = affinityRMS(pro.cc,SubLevel);
            const Equilibrium &eq = pro.eq;
            Cend.ld(pro.cc);
            Solver & F = *this;
            XTriplet x = { zero,   0, one    };
            XTriplet f = { pro.W0, 0, pro.W1 };

            //Y_XMLog(xml, eq.name << " " << f.a.str() << "/" << F(0).str() << " -> " << f.c.str() << " / " << F(1).str() );

            if(xml.verbose)
            {
                ( xml() << eq.name << " [").flush();
            }


            {
                const String fn = pro.eq.name + ".dat";
                OutputFile   fp(fn);
                const unsigned np = 500;
                for(unsigned i=0;i<=np;++i)
                {
                    const double u = (i / (double(np)));
                    fp("%.15g %s\n", u, (*this)(u).str().c_str());
                }
            }



            // set a to minimum
            if(f.a>f.c) { Swap(f.a,f.c); Swap(x.a,x.c); }
            assert(f.a<=f.c);



            for(size_t iter=1;iter<=MaxIter;++iter)
            {
                assert(f.a<=f.c);
                f.b = F(x.b=x.middle()); assert( x.isOrdered() );
                //std::cerr << "iter=" << iter << "/" << MaxIter << " " << x << " -> " << f << std::endl;
                if(xml.verbose) (xml.os << '.').flush();
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

            //std::cerr << "Global Min@" << x.a << std::endl;
            pro.Wo = F(x.a);
            pos = "global";
            goto FINALIZE;

        OPTIMIZE:
            //std::cerr << "Local around " << x.b << std::endl;
            assert(f.isLocalMinimum());
            (void) Optimize<xreal_t>::Run(F,x,f);
            pos    = "local";
            pro.Wo = f.b;

        FINALIZE:
            if(xml.verbose) (xml.os << "] @" << pro.Wo.str()  << " / " << pos) << std::endl;

            pro.cc.ld(Ctry);
            pro.xi = eq.extent(xadd,pro.cc,SubLevel,Csub);
            return;
        }
    }

}


