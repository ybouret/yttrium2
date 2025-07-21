
template <>
void Optimize<real_t>:: Run(Triplet<real_t> & x,
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
        ParabolicOptimization<real_t>::Step(x,f,F);
        if( AlmostEqual<real_t>::Are(x_old,x.b) )
        {
            return;
        }

    }

}
