
namespace
{

}

template <>
bool Bracket<real_t>:: Inside(Triplet<real_t> &x,
                              Triplet<real_t> &f,
                              FunctionType    &F)
{
    if(f.a>f.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }
    assert(f.a<=f.c);

#if 0
    const real_t _0(0);
    real_t xx[4] = { _0,_0,_0,_0  };
    real_t ff[4] = { _0,_0,_0,_0  };
#endif

    // initial guess
    f.b = F( x.b = x.middle() ); assert( x.isOrdered() );
    while( !f.isLocalMinimum() )
    {
        assert(f.a<=f.c);
        assert(f.b>f.a);

    }

    assert( f.isLocalMinimum() );
    return true;
}
