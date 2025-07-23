
template <>
ZBis<real_t>:: ZBis() noexcept : ZFind<real_t>()
{

}

template <>
ZBis<real_t>:: ~ZBis() noexcept
{

}

template <>
const char * ZBis<real_t>:: callSign() const noexcept
{
    return ZBisCallSign;
}

template <>
real_t ZBis<real_t>:: lookup(Triplet<real_t> &x, Triplet<real_t> &f, FunctionType &F)
{
    Handle hx = { 0,0 };
    Handle hf = { 0,0 };

    //--------------------------------------------------------------------------
    //
    // check and organize data
    //
    //--------------------------------------------------------------------------
    if( found(hx, hf, x, f, F) ) return x.b;

    //--------------------------------------------------------------------------
    //
    // initial bisection
    //
    //--------------------------------------------------------------------------
    switch( Sign::Of( f.b = F(x.b=Half<real_t>::Of(x.a,x.c) ) ) )
    {
        case __Zero__: // exact
            return x.b;

        case Negative:
            *hx.neg = x.b;
            *hf.neg = f.b;
            break;

        case Positive:
            *hx.pos = x.b;
            *hf.pos = f.b;
            break;
    }

    real_t width = x.width();
    while(true)
    {
        const real_t x_old = x.b;
        switch( Sign::Of( f.b = F(x.b=Half<real_t>::Of(x.a+x.c) ) ) )
        {
            case __Zero__: // exact
                return x.b;

            case Negative:
                *hx.neg = x.b;
                *hf.neg = f.b;
                break;

            case Positive:
                *hx.pos = x.b;
                *hf.pos = f.b;
                break;
        }

        if( AlmostEqual<real_t>::Are(x_old,x.b) )
            return x.b;

        const real_t newWidth = x.width();
        if( newWidth >= width )
        {
            // width stagnation
            return x.b;
        }
        width = newWidth;
    }

}
