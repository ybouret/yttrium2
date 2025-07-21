
template <>
real_t Optimize<real_t>:: Run(Triplet<real_t> & x,
                            Triplet<real_t> & f,
                            FunctionType &    F)
{

    // prepare data
    assert(x.isOrdered());
    assert(f.isLocalMinimum());
    if(x.a>x.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(x.isIncreasing());
    assert(f.isLocalMinimum());

    // run
    while(true)
    {
        const real_t x_old = x.b;
        ParabolicStep<real_t>::Tighten(x,f,F);
        std::cerr << "x_old = " << x_old << " -> " << x.b << std::endl;
        if( AlmostEqual<real_t>::Are(x_old,x.b) )
        {
            f.b = F(x.b);
            return x.b;
        }

    }

}
