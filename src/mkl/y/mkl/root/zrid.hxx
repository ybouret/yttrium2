
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
    {
        Handle hx = { 0,0 };
        Handle hf = { 0,0 };

        if( found(hx, hf, x, f, F) ) return;
    }



}


