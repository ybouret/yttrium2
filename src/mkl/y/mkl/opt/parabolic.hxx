
namespace
{
    static inline
    void Extract(Triplet<real_t> & x,
                 Triplet<real_t> & f,
                 real_t            xx[],
                 real_t            ff[],
                 const size_t      np)
    {
        //----------------------------------------------------------------------
        // sorting
        //----------------------------------------------------------------------
        assert(np>=3);
        if(ParabolicStepVerbose)
        {
            Core::Display(std::cerr << PFX << "raw_xx=",xx,np) << std::endl;
            Core::Display(std::cerr << PFX << "raw_ff=",ff,np) << std::endl;
        }
        Sorting::Heap::Sort(xx,ff,np,Sign::Increasing<real_t>);

        if(ParabolicStepVerbose)
        {
            Core::Display(std::cerr << PFX << "srt_xx=",xx,np) << std::endl;
            Core::Display(std::cerr << PFX << "srt_ff=",ff,np) << std::endl;

            OutputFile fp("_para.dat");
            for(size_t i=0;i<np;++i) fp("%.15g %.15g\n", double(xx[i]), double(ff[i]));

        }




        size_t       imin = 0;
        real_t       fmin = ff[0];
        const size_t itop = np-1;
        for(size_t i=1;i<=itop;++i)
        {
            const real_t ftmp = ff[i];
            if(ftmp<fmin)
            {
                fmin = ftmp;
                imin = i;
            }
        }
        Y_PRINT("fmin=" << fmin << " #" << imin);

        if(imin<=0)
        {
            x.a = x.b = xx[0]; x.c = xx[1];
            f.a = f.b = fmin;  f.c = ff[1];
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
            return;
        }

        if(imin>=itop)
        {
            x.b = x.c = xx[imin];
            f.b = f.c = xx[imin];
            --imin;
            x.a = xx[imin];
            f.a = ff[imin];
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
            return;
        }

        assert(imin>0);
        assert(imin<itop);
        --imin;
        x.load(xx + imin);
        f.load(ff + imin);

        assert(x.isIncreasing());
        assert(f.isLocalMinimum());


    }
}

template <>
void ParabolicStep<real_t>:: Tighten(Triplet<real_t> & x,
                                     Triplet<real_t> & f,
                                     FunctionType &    F)
{

    assert( x.isIncreasing()   );
    assert( f.isLocalMinimum() );

    //--------------------------------------------------------------------------
    //
    // preparing data
    //
    //--------------------------------------------------------------------------
    Y_PRINT("<enter> x=" << x << "; f=" << f);

    const real_t _0(0);
    real_t xx[5] = {_0,_0,_0,_0,_0};
    real_t ff[5] = {_0,_0,_0,_0,_0};

    //--------------------------------------------------------------------------
    //
    // Intercepting side cases
    //
    //--------------------------------------------------------------------------
    if(x.b<=x.a || x.b >= x.c)
    {
        xx[0] = x.a;        ff[0] = f.a;
        xx[1] = x.middle(); ff[1] = F(xx[1]);
        xx[2] = x.c;        ff[2] = f.c;
        Y_PRINT("<on side> inserting F(" << xx[1] << ")=" << ff[1]);
        return Extract(x,f,xx,ff,3);
    }

    assert(x.a < x.b);
    assert(x.b < x.c);

    // at this point, beta exists

    //--------------------------------------------------------------------------
    //
    // check f
    //
    //--------------------------------------------------------------------------
    real_t g0 = f.a - f.b; assert( g0 >= _0  );
    real_t g1 = f.c - f.b; assert( g1 >= _0  );

    if(g0 <= _0 || g1 <= _0 || AlmostEqual<real_t>::Are(g0,g1) )
    {

        //----------------------------------------------------------------------
        // add two middle points to scan
        //----------------------------------------------------------------------
        Y_PRINT("<degenerate> g0=" <<  g0 << " : g1=" << g1);
        x.save(xx);
        f.save(ff);
        ff[3] = F( xx[3] = Half<real_t>::Of(x.a,x.b));
        ff[4] = F( xx[4] = Half<real_t>::Of(x.b,x.c));
        return Extract(x,f,xx,ff,5);
    }

    assert(g0>_0);
    assert(g1>_0);
    Y_PRINT("<generic> g0=" <<  g0 << " : g1=" << g1);

    const real_t _1(1);
    const SignType balance = Sign::Of(g0,g1);
    switch( balance )
    {
        case Negative: assert(g0<g1); g0/=g1; g1=_1; break;
        case __Zero__:                g0=g1=_1;      break; // intercepted...
        case Positive: assert(g1<g0); g1/=g0; g0=_1; break;
    }
    Y_PRINT("<scaling> g0=" <<  g0 << " : g1=" << g1);

    // save current triple
    x.save(xx);
    f.save(ff);

    // append parabolic point
    const real_t width = x.width(); assert( width > _0 );
    const real_t beta  = Clamp(_0,(x.b-x.a)/width,_1);
    const real_t omb   = Clamp(_0,(x.c-x.b)/width,_1);
    const real_t kappa = ( beta * omb * (g0-g1) )/( omb*g0 + beta * g1);
    const real_t k_w   = kappa * width;
    const real_t dx    = Half<real_t>::Of(k_w);            // |dx| <= w/4
    const real_t xp    = Clamp(x.a,x.middle() + dx , x.c); // predicted parabolic point
    const real_t fp    = F(xp );                           // value
    Y_PRINT("<predicted> xp=" << xp << " (dx=" << dx <<") fp=" << fp);
    




    return Extract(x,f,xx,ff,5);




    






}
