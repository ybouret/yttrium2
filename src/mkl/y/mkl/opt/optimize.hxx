

static inline bool isFlat(const Triplet<real_t> &f)
{
    assert(f.isLocalMinimum());
    const real_t fmax = Max(f.a,f.c);
    return AlmostEqual<real_t>::Are(fmax,f.b);
}

static inline bool isPunctual(const Triplet<real_t> &x)
{
    assert(x.isIncreasing() );
    return AlmostEqual<real_t>::Are(x.a,x.b) &&  AlmostEqual<real_t>::Are(x.c,x.b);
}


template <>
real_t Optimize<real_t>:: Run(Triplet<real_t> & x,
                              Triplet<real_t> & f,
                              FunctionType &    F)
{

    //__________________________________________________________________________
    //
    //
    // prepare data
    //
    //__________________________________________________________________________
    assert(x.isOrdered());
    assert(f.isLocalMinimum());
    if(x.a>x.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    //__________________________________________________________________________
    //
    //
    // run
    //
    //__________________________________________________________________________
    //std::cerr.precision(15);
    while(true)
    {
        ParabolicStep<real_t>::Tighten(x,f,F);
        //std::cerr << "x=" << x << ", f=" << f << " df=" << Max(f.a,f.c)-f.b << std::endl;
        assert(x.isIncreasing());
        assert(f.isLocalMinimum());

        if( isFlat(f) )
        {
            //std::cerr << "flat" << std::endl;
            break;
        }

        if( isPunctual(x) )
        {
            //std::cerr << "ponctual" << std::endl;
            break;
        }

    }

    f.b = F(x.b);
    return x.b;
}
