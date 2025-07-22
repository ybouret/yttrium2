
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
    real_t width = x.width();
    while(true)
    {
        const real_t newWidth = ParabolicStep<real_t>::Tighten(x,f,F);
        if( AlmostEqual<real_t>::Are(width,newWidth) )
        {
            f.b = F(x.b);
            return x.b;
        }
        width = newWidth;
    }

}
