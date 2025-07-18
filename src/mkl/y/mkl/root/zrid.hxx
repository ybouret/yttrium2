
template <>
ZRid<real_t>:: ZRid() noexcept : ZFind<real_t>()
{

}

template <>
ZRid<real_t>:: ~ZRid() noexcept
{

}

template <>
const char * ZRid<real_t>:: callSign() const noexcept
{
    return ZRidCallSign;
}

template <>
void ZRid<real_t>:: lookup(Triplet<real_t> &x, Triplet<real_t> &f, FunctionType &F)
{
    //--------------------------------------------------------------------------
    //
    // check and organize data
    //
    //-------------------------------------------------------------------------_

        Handle hx = { 0,0 };
        Handle hf = { 0,0 };

        if( found(hx, hf, x, f, F) ) return;


    const bool increasing = (hf.neg == &f.a);


    {
        assert( Sign::LTZ(*hf.neg) );
        assert( Sign::GTZ(*hf.pos) );
        f.b = F( x.b=Half<real_t>::Of(x.a+x.c) );
        const SignType s_b = Sign::Of(f.b); if(__Zero__==s_b) { return; }

        const real_t scaling = Max( Fabs<real_t>::Of(f.a), Fabs<real_t>::Of(f.b), Fabs<real_t>::Of(f.c) );
        const real_t f_h     = f.b/scaling;
        const real_t Delta   = f_h * f_h - (f.a/scaling)*(f.c/scaling); assert( Sign::GTZ(Delta) );

    }


}


