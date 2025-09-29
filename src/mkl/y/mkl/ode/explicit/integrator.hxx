
template <>
class ExplicitIntegrator<real_t>:: Code : public Object
{
public:

    inline explicit Code() :
    Object(),
    driver(),
    y(), dydx(), yscal(),
    xadd(),
    zero(0),
    TINY(1e-30)
    {

    }


    inline virtual ~Code() noexcept
    {

    }


    inline void run(Writable<real_t> & ystart,
                    const real_t       x1,
                    const real_t       x2,
                    const real_t       h1,
                    const real_t       eps,
                    Equation &         eq,
                    Callback * const   cb,
                    StepType   &       step)
    {
        //----------------------------------------------------------------------
        //
        //
        // initialize
        //
        //
        //----------------------------------------------------------------------
        Iter::Direction d = Iter::Forward;
        const size_t    n = ystart.size(); prepare(n);
        real_t          h = Fabs<real_t>::Of(h1);
        switch( Sign::Of(x2,x1) )
        {
            case __Zero__:
                return;

            case Positive:
                assert(x2>x1);
                h = Min(h,x2-x1);
                break;

            case Negative:
                assert(x2<x1);
                d = Iter::Reverse;
                h = -Min(h,x1-x2);
                break;
        }

        real_t                  x    = x1;
        for(size_t i=n;i>0;--i) y[i] = ystart[i];

        //----------------------------------------------------------------------
        //
        //
        // loop
        //
        //
        //----------------------------------------------------------------------
        while(true)
        {
            //------------------------------------------------------------------
            //
            // evaluate dydx at x,y
            //
            //------------------------------------------------------------------
            eq(dydx,x,y);

            for(size_t i=n;i>0;--i)
            {
                xadd = TINY;
                xadd += Fabs<real_t>::Of( y[i] );
                const real_t dy = h * dydx[i];
                xadd += Fabs<real_t>::Of( dy );
                yscal[i] = xadd.sum();
            }
            
            //------------------------------------------------------------------
            //
            // check step length
            //
            //------------------------------------------------------------------
            bool last = false;
            switch(d)
            {
                case Iter::Forward:
                    if(x+h>=x2) { h=x2-x; last=true; }
                    break;
                case Iter::Reverse:
                    if(x+h<=x2) { h=x2-x; last=true; }
                    break;
            }

            //------------------------------------------------------------------
            //
            // make a controlled step
            //
            //------------------------------------------------------------------
            real_t hdid = zero, hnext= zero;
            driver(step,y,x,dydx,yscal,h,hdid,hnext,eps,eq,cb);


            //------------------------------------------------------------------
            //
            // check if done
            //
            //------------------------------------------------------------------
            if( last && Fabs<real_t>::Of(hdid) >= Fabs<real_t>::Of(h) )
            {
                // done
                for(size_t i=n;i>0;--i) ystart[i] = y[i];
                return;
            }

            //------------------------------------------------------------------
            //
            // check next step
            //
            //------------------------------------------------------------------
            const real_t ah = Fabs<real_t>::Of(hnext);
            if( AlmostEqual<real_t>::Are(ah,zero) )
                throw Specific::Exception(step.callSign(),"step underflow");

            h = hnext;
        }



    }

    ExplicitDriver<real_t>  driver;
    Vector<real_t> y, dydx, yscal;
    Cameo::Addition<real_t> xadd;
    const real_t            zero;
    const real_t            TINY;

private:
    Y_Disable_Copy_And_Assign(Code);
    inline void prepare(const size_t n)
    {
        y.adjust(n,zero);
        dydx.adjust(n,zero);
        yscal.adjust(n,zero);
    }
};


template <>
ExplicitIntegrator<real_t>::  ExplicitIntegrator() :
eps( 1.0e-7 ),
code( new Code() )
{
}

template <>
ExplicitIntegrator<real_t>:: ~ExplicitIntegrator() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
void ExplicitIntegrator<real_t>:: operator()(Writable<real_t> & ystart,
                                             const real_t       x1,
                                             const real_t       x2,
                                             const real_t       h1,
                                             Equation &         eq,
                                             Callback * const   cb,
                                             StepType   &       step)
{
    assert(code);
    code->run(ystart,x1,x2,h1,eps,eq,cb,step);
}
