
namespace
{
    static inline
    void Extract(Triplet<real_t> & x,
                 Triplet<real_t> & f,
                 real_t            xx[],
                 real_t            ff[],
                 const size_t      np)
    {
        assert(np>=3);
        Sorting::Heap::Sort(xx,ff,np,Sign::Increasing<real_t>);

#if 0
        if(ParabolicOptimizationVerbose)
        {
            Core::Display(std::cerr << PFX << "xx=",xx,np) << std::endl;
            Core::Display(std::cerr << PFX << "ff=",ff,np) << std::endl;
        }
#endif

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
        //Y_PRINT("fmin=" << fmin << " #" << imin);

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
            x.b = x.c = xx[imin]; x.a = xx[imin-1];
            f.b = f.c = xx[imin]; f.a = ff[imin-1];
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

        Y_PRINT("<leave> x=" << x << "; f=" << f);

    }
}

template <>
void ParabolicOptimization<real_t>:: Step(Triplet<real_t> & x,
                                          Triplet<real_t> & f,
                                          FunctionType &    F)
{

    Y_PRINT("<enter> x=" << x << "; f=" << f);
    assert( x.isIncreasing()   );
    assert( f.isLocalMinimum() );

    const real_t _0(0);

    real_t xx[5] = {_0,_0,_0,_0,_0};
    real_t ff[5] = {_0,_0,_0,_0,_0};



    if(x.b<=x.a)
    {
        Y_PRINT("<at left>");
        assert( f.a <= f.b );
        xx[0] = x.a; ff[0] = f.a;
        ff[1] = F(xx[1] = x.middle());
        xx[2] = x.c; ff[2] = f.c;
        return Extract(x,f,xx,ff,3);
    }

    if(x.b>=x.c)
    {
        Y_PRINT("<at right>");
        assert(f.c <= f.b);
        xx[0] = x.a; ff[0] = f.a;
        ff[1] = F(xx[1] = x.middle());
        xx[2] = x.c; ff[2] = f.c;
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
    real_t       g0 = f.a - f.b; assert( g0 >= _0  );
    real_t       g1 = f.c - f.b; assert( g1 >= _0  );

    if(g0 <= _0 || g1 <= _0)
    {
        x.save(xx); f.save(ff);
        ff[3] = F( xx[3] = Half<real_t>::Of(x.a,x.b) );
        ff[4] = F( xx[4] = Half<real_t>::Of(x.b,x.c) );
        return Extract(x,f,xx,ff,5);
    }
    else
    {
        assert(g0 > _0); assert( g1 > _0);
        // most generic case
        const real_t _1(1);
        switch( Sign::Of(g0,g1) )
        {
            case Negative: assert(g0<g1); g0/=g1; g1=_1; break;
            case __Zero__:                g0=g1=_1;      break;
            case Positive: assert(g1<g0); g1/=g0; g0=_1; break;
        }

        const real_t width = x.width(); assert( Sign::GTZ(width) );
        const real_t beta  = Clamp(_0,(x.b-x.a)/width,_1);
        const real_t omb   = Clamp(_0,(x.c-x.b)/width,_1);
        const real_t two_w = (_1 - ( beta * omb * (g1-g0) )/( omb*g0 + beta * g1)) * width;
        x.save(xx);
        f.save(ff);
        ff[3] = F( xx[3] = Clamp(x.a,x.a+Half<real_t>::Of(two_w),x.c) );
        if( xx[3] <= x.b )
        {
            ff[4] = F( xx[4] = Half<real_t>::Of(x.b,x.c) );
        }
        else
        {
            ff[4] = F( xx[4] = Half<real_t>::Of(x.b,x.a) );
        }
        return Extract(x,f,xx,ff,5);
    }






}
