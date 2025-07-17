
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


    for(size_t i=0;i<1000;++i)
    {
        std::cerr << "@" << i <<":  x=" << x << "; f=" << f << std::endl;

        const real_t x_old = x.b;
        switch( Sign::Of( f.b = F(x.b=Half<real_t>::Of(x.a+x.c) ) ) )
        {
            case __Zero__: // exact
                std::cerr << f.b << " @" << x.b << std::endl;
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

        const real_t thr = Numeric<real_t>::MIN/Numeric<real_t>::EPSILON;
        const real_t del = Fabs<real_t>::Of(x.b - x_old);
        const real_t den = Max( Min(Fabs<real_t>::Of(x.b),Fabs<real_t>::Of(x_old)), thr);
        std::cerr << x_old << " -> " << x.b
        << " : = " << ASCII::Boolean::text( AlmostEqual<real_t>::Are(x_old,x.b) )
        << " | thr = " << thr
        << " | del = " << del
        << " | den = " << den
        <<  std::endl;


    }

}
