
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

namespace
{
    static inline
    real_t Extract(Triplet<real_t> &x,
                 Triplet<real_t>   &f,
                 real_t             xx[],
                 real_t             ff[])
    {
      
        Sorting::Heap::Sort(xx,ff,4, Sign::Increasing<real_t>);
        for(unsigned i=0,j=1;i<3;++i,++j)
        {
            f.a = ff[i];
            f.c = ff[j];
            if( Sign::AreOpposite( Sign::Of(f.a), Sign::Of(f.c) ) )
            {
                x.a = xx[i]; x.c = xx[j];

                if( Fabs<real_t>::Of(f.a) <= Fabs<real_t>::Of(f.c) )
                {
                    x.b = x.a;
                    f.b = f.a;
                }
                else
                {
                    x.b = x.c;
                    f.b = f.c;
                }
                return x.width();
            }
        }
        
        throw Specific::Exception(ZRidCallSign,"corrupted algorithm");
    }
}

template <>
void ZRid<real_t>:: lookup(Triplet<real_t> &x, Triplet<real_t> &f, FunctionType &F)
{
    //--------------------------------------------------------------------------
    //
    // check and organize data
    //
    //--------------------------------------------------------------------------
    {
        Handle hx = { 0,0 };
        Handle hf = { 0,0 };

        if( found(hx, hf, x, f, F) ) return;
    }

    if(x.a>x.c)
    {
        Swap(x.a,x.c);
        Swap(f.a,f.c);
    }

    //--------------------------------------------------------------------------
    //
    // Loop
    //
    //--------------------------------------------------------------------------
    const real_t zero(0);
    real_t       width = x.width();
    while(true)
    {
        // take midpoint
        const SignType s_b = Sign::Of( f.b = F( x.b=Half<real_t>::Of(x.a+x.c) ));
        if(__Zero__==s_b) { return; }

        // prepare possibilities
        real_t xx[4] = { x.a, x.b, x.c, zero };
        real_t ff[4] = { f.a, f.b, f.c, zero };

        // Ridder's
        const real_t scaling    = Max( Fabs<real_t>::Of(f.a), Fabs<real_t>::Of(f.b), Fabs<real_t>::Of(f.c) ); assert( Sign::GTZ(scaling) );
        const real_t f_h        = f.b/scaling;
        const real_t D          = f_h * f_h - (f.a/scaling)*(f.c/scaling); assert(Sign::GTZ(D));
        const real_t S          = Sqrt<real_t>::Of(D);
        const real_t sdx        = (f_h / S) * (x.c-x.a);
        const real_t adx        = Fabs<real_t>::Of(sdx);
        const real_t dx         = Half<real_t>::Of(adx);
        const bool   increasing = Sign::LTZ(f.a);
        if( increasing )
        {
            assert( Sign::LTZ(f.a) ); // f.a < 0
            assert( Sign::GTZ(f.c) ); // f.c > 0
            if( Negative == s_b )
            {
                xx[3] = Clamp(x.b,x.b+dx,x.c);
            }
            else
            {
                xx[3] = Clamp(x.a,x.b-dx,x.b);
            }
        }
        else
        {
            assert( Sign::GTZ(f.a) ); // f.a > 0
            assert( Sign::LTZ(f.c) ); // f.c < 0
            if( Negative == s_b )
            {
                xx[3] = Clamp(x.a,x.b-dx,x.b);
            }
            else
            {
                xx[3] = Clamp(x.b,x.b+dx,x.c);
            }
        }

        ff[3] = F(xx[3]);

        if( __Zero__ == Sign::Of(ff[3]) )
        {
            x.b = xx[3];
            f.b = ff[3];
            return;
        }

        const real_t newWidth = Extract(x,f,xx,ff);

        if( AlmostEqual<real_t>::Are(width,newWidth) )
        {
            return;
        }
        width = newWidth;
    }




}


