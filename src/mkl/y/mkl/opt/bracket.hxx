
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


PROBE:
    // make new guess
    f.b = F( x.b = x.middle() ); assert( x.isOrdered() );

    // test against the minimal value
    switch( Sign::Of(f.b,f.a) )
    {
        case __Zero__:
        case Negative:
            // success
            assert(f.isLocalMinimum());
            break;

            // not there yet
        case Positive:
            f.c = f.b;
            x.c = x.b;
            assert( x.isOrdered() );
            if( AlmostEqual<real_t>::Are(x.a,x.b) )
            {
                f.b = f.a;
                x.b = x.a;
                assert( x.isOrdered() );
                assert( f.isLocalMinimum() );
                return false; // global mininum on side
            }
            goto PROBE;
    }



    return true;


}
