
template <>
class ExplicitDriver<real_t>:: Code : public Object
{
public:
    typedef FCPU<real_t>::Type fcpu_t;

    inline explicit Code() :
    Object(),
    yerr(),
    ytemp(),
    zero(0),
    one(1),
    CUT(0.1),
    five(5),
    SAFETY(SAFETY_VALUE),
    PGROW(-0.2),
    PSHRINK(-0.25),
    ERRCON(1.89e-4)
    {
    }

    inline virtual ~Code() noexcept
    {
    }

    inline void run(StepType               & step,
                    Writable<real_t>       & y,
                    real_t                 & x,
                    const Readable<real_t> & dydx,
                    const Readable<real_t> & yscal,
                    const real_t             htry,
                    real_t                 & hdid,
                    real_t                 & hnext,
                    const real_t             eps,
                    Equation &               eq,
                    Callback * const         cb)
    {
        const size_t n      = y.size(); prepare(n);
        real_t       h      = htry;
        real_t       errmax = zero;

        // trials with step reduction
        while(true)
        {
            step(ytemp,yerr,y,dydx,x,htry,eq,cb);

            // check accuracy
            errmax = zero;
            for(size_t i=n;i>0;--i) {
                const real_t err = yerr[i]/yscal[i];
                InSituMax(errmax, Fabs<real_t>::Of(err));
            }
            errmax /= eps;
            if(errmax<=one) break;

            // step reduction
            const real_t htemp = SAFETY*h*std::pow(errmax,PSHRINK);
            h = (h >= zero ? Max(htemp,CUT*h) : Min(htemp,CUT*h));
            volatile real_t xnew = x + h;
            if(same(xnew,x))
                throw Specific::Exception(step.callSign(),"step size underflow");

        }

        // compute hnext from control value
        if (errmax > ERRCON)
            hnext=SAFETY*h*std::pow(errmax,PGROW);
        else
            hnext=five*h;

        // update x
        x += (hdid=h);
    }

    Vector<real_t> yerr;
    Vector<real_t> ytemp;
    const real_t   zero;
    const real_t   one;
    const real_t   CUT;
    const real_t   five;
    const real_t   SAFETY;
    const fcpu_t   PGROW;
    const fcpu_t   PSHRINK;
    const fcpu_t   ERRCON;
private:
    Y_Disable_Copy_And_Assign(Code);
    inline void prepare(const size_t n)
    {
        yerr.adjust(n,zero);
        ytemp.adjust(n,zero);
    }

    inline bool same(const real_t a, const real_t b) const noexcept
    {
        const real_t delta = a-b;
        const real_t adiff = Fabs<real_t>::Of(delta);
        return adiff <= zero;
    }
};


template <>
ExplicitDriver<real_t>:: ExplicitDriver() : code( new Code()  )
{
}


template <>
ExplicitDriver<real_t>:: ~ExplicitDriver() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
void ExplicitDriver<real_t>:: operator()  (StepType               & step,
                                           Writable<real_t>       & y,
                                           real_t                 & x,
                                           const Readable<real_t> & dydx,
                                           const Readable<real_t> & yscal,
                                           const real_t             htry,
                                           real_t                 & hdid,
                                           real_t                 & hnext,
                                           const real_t             eps,
                                           Equation &               eq,
                                           Callback * const         cb)
{
    assert(code);
    code->run(step, y, x, dydx, yscal, htry, hdid, hnext, eps, eq, cb);
}
