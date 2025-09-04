
#include "y/chemical/plexus/solver.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        using namespace MKL;

        xreal_t Solver:: minimize(XMLog &xml, const xreal_t W0, const xreal_t W1)
        {
            static const size_t MaxIter = ceil( -log( Numeric<real_t>::EPSILON) / log(2.0) );

            Solver & F = *this;
            XTriplet x = { zero, 0, one };
            XTriplet f = { W0,   0, W1  };
            bool     isLocal = true;

            //------------------------------------------------------------------
            //
            //
            // set a to minimum
            //
            //
            //------------------------------------------------------------------
            if(f.a>f.c) { Swap(f.a,f.c); Swap(x.a,x.c); }
            assert(f.a<=f.c);

            //------------------------------------------------------------------
            //
            //
            // Loop to Epsilon precision
            //
            //
            //------------------------------------------------------------------
            if( xml.verbose ) (xml.os << " [");
            for(size_t iter=1;iter<=MaxIter;++iter)
            {
                assert(f.a<=f.c);
                if( xml.verbose ) (xml.os << '.').flush();
                f.b = F(x.b=x.middle()); assert( x.isOrdered() );
                if(f.b <= f.a )
                {
                    //----------------------------------------------------------
                    //
                    // Local Minimum
                    //
                    //----------------------------------------------------------
                    assert(f.isLocalMinimum());
                    (void) Optimize<xreal_t>::Run(F,x,f);
                    if(xml.verbose)
                    {
                        for(;iter<MaxIter;++iter) xml.os << '#';
                    }
                    goto END;
                }

                assert(f.b>f.a);
                x.c = x.b;
                f.c = f.b;
                if( AlmostEqual<xreal_t>::Are(f.a,f.b) && AlmostEqual<xreal_t>::Are(f.b,f.c) )
                {
                    //----------------------------------------------------------
                    //
                    // Local Flat
                    //
                    //----------------------------------------------------------
                    if(xml.verbose) for(;iter<MaxIter;++iter) xml.os << '-';
                    break;
                }
            }

            //----------------------------------------------------------
            //
            // Global Minimum at x.a
            //
            //----------------------------------------------------------
            isLocal = false;
            f.b = f.c = f.a = F(x.b = x.c = x.a);

        END:
            if(xml.verbose) {
                xml.os << "] @" << std::setw(22) << f.b.str() << ' ';
                xml.os << (isLocal ? "local" : "global");
                xml.os << std::endl;
            }

            return f.b;
        }

    }

}


