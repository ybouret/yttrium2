
template <>
class ExplicitDriver<real_t>:: Code : public Object
{
public:

    inline explicit Code() :
    Object(),
    zero(0),
    one(1),
    SAFETY(0.9)
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
        const size_t n = y.size(); prepare(n);
        real_t       h = htry;

        while(true)
        {
            step(ytemp,yerr,y,dydx,x,htry,eq,cb);

            // check accuracy
            {
                real_t errmax = zero;
                for(size_t i=n;i>0;--i) {
                    const real_t err = yerr[i]/yscal[i];
                    InSituMax(errmax, Fabs<real_t>::Of(err));
                }
                errmax /= eps;
                if(errmax<=one) break;
            }


        }

    }

    Vector<real_t> yerr;
    Vector<real_t> ytemp;
    const real_t   zero;
    const real_t   one;
    const real_t   SAFETY;

private:
    Y_Disable_Copy_And_Assign(Code);
    inline void prepare(const size_t n)
    {
        yerr.adjust(n,zero);
        ytemp.adjust(n,zero);
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
