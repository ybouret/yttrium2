
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
        f.b = F( x.b=Half<real_t>::Of(x.a+x.c) );
        const SignType s_b = Sign::Of(f.b);
        switch(s_b)
        {
            case __Zero__:
                // exact
                return;
        }

    }


}


