
template <>
class ExplicitIntegrator<real_t>:: Code : public Object
{
public:

    inline explicit Code() : Object(), zero(0)
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
                    DriverType &       driver,
                    StepType   &       step)
    {
        // initialize
        Iter::Direction d = Iter::Forward;
        const size_t    n = ystart.size(); prepare(n);
        real_t          h = Fabs<real_t>::Of(h1);
        switch( Sign::Of(x2,x1) )
        {
            case __Zero__: return;
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

        real_t                  x     = x1;
        for(size_t i=n;i>0;--i) y[i] = ystart[i];

        // loop
        {
            eq(dydx,x,y);
            
        }



    }


    Vector<real_t> y, dydx, yscal;
    const real_t zero;

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
ExplicitIntegrator<real_t>::  ExplicitIntegrator() : code( new Code() )
{
}

template <>
ExplicitIntegrator<real_t>:: ~ExplicitIntegrator() noexcept
{
    assert(code);
    Destroy(code);
}
