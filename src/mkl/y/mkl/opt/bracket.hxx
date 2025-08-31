
namespace
{

}

template <>
bool Bracket<real_t>:: Inside(Triplet<real_t> &x,
                              Triplet<real_t> &f,
                              FunctionType    &F)
{
    //--------------------------------------------------------------------------
    //
    // initialize with lowest at a
    //
    //--------------------------------------------------------------------------
    if(f.a>f.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(f.a<=f.c);



    Y_PRINT("from F(" << x.a << ")=" << f.a << " to F(" << x.c << ")=" << f.c);

    real_t width = x.width();
PROBE:
    //--------------------------------------------------------------------------
    //
    // make new guess
    //
    //--------------------------------------------------------------------------
    f.b = F( x.b = x.middle() );
    assert( x.isOrdered() );
    assert(f.a<=f.c);

    Y_PRINT("try x=" << x << "; f=" << f << "; dx = " << Fabs<real_t>::Of(x.a-x.b) << "; w=" << Fabs<real_t>::Of(x.a-x.c) << "; df=" << f.b-f.a);

    //--------------------------------------------------------------------------
    //
    // test against the minimal value
    //
    //--------------------------------------------------------------------------
    switch( Sign::Of(f.b,f.a) )
    {
        case __Zero__:
        case Negative:
            //------------------------------------------------------------------
            // success
            //------------------------------------------------------------------
            assert(f.isLocalMinimum());
            assert(x.isOrdered());
            Y_PRINT("found local min");
            if( AlmostEqual<real_t>::Are(x.a,x.b) )
            {
                Y_PRINT("but global");
                goto GLOBAL;
            }
            if(x.a>x.c)
            {
                Swap(x.a,x.c);
                Swap(f.a,f.c);
            }
            assert(x.isIncreasing());
            assert(f.isLocalMinimum());
            return true;


        case Positive: {
            //------------------------------------------------------------------
            // not there yet: move c to b for next step
            //------------------------------------------------------------------
            assert(f.b>f.a);
            assert( x.isOrdered() );
            assert( !f.isLocalMinimum() );

            if( AlmostEqual<real_t>::Are(x.a,x.b) )
            {
                Y_PRINT("convergence");
                goto GLOBAL;
            }


            f.c = f.b;
            x.c = x.b;

            {
                const real_t newWidth = x.width();
                if(newWidth>=width)
                {
                    Y_PRINT("width stagnation");
                    goto GLOBAL;
                }
                width = newWidth;
            }


        }  goto PROBE;
    }

GLOBAL:
    f.c = f.b; x.c = x.b;
    f.b = f.a; x.b = x.a;
    return false;
}
