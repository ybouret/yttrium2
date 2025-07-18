
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
void ZBis<real_t>:: lookup(Triplet<real_t> &x, Triplet<real_t> &f, FunctionType &F)
{
    Handle hx = { 0,0 };
    Handle hf = { 0,0 };

    //--------------------------------------------------------------------------
    //
    // check and organize data
    //
    //--------------------------------------------------------------------------
    if( found(hx, hf, x, f, F) ) return;

    //--------------------------------------------------------------------------
    //
    // initial bisection
    //
    //--------------------------------------------------------------------------
    switch( Sign::Of( f.b = F(x.b=Half<real_t>::Of(x.a+x.c) ) ) )
    {
        case __Zero__: // exact
            return;

        case Negative:
            *hx.neg = x.b;
            *hf.neg = f.b;
            break;

        case Positive:
            *hx.pos = x.b;
            *hf.pos = f.b;
            break;
    }


    //size_t cycle=0;
    while(true)
    {
        //++cycle;
        //std::cerr << "@" << cycle <<":  x=" << x << "; f=" << f << std::endl;

        const real_t x_old = x.b;
        switch( Sign::Of( f.b = F(x.b=Half<real_t>::Of(x.a+x.c) ) ) )
        {
            case __Zero__: // exact
                //std::cerr << "exact " << f.b << " @" << x.b << std::endl;
                return;

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
            return;
    }

}
