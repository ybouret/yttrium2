
template <>
class RK4<real_t>::Code : public Object
{
public:

    inline explicit Code(const size_t nmax) :
    Object(),
    yt(WithAtLeast,nmax),
    k2(WithAtLeast,nmax),
    k3(WithAtLeast,nmax),
    k4(WithAtLeast,nmax),
    xadd(),
    zero(0),
    half(0.5),
    six(6)
    {
    }

    inline virtual ~Code() noexcept
    {
    }

    void run(Writable<real_t> &       yout,
             const Readable<real_t> & y,
             const Readable<real_t> & k1,
             const real_t             x,
             const real_t             h,
             Equation &               f,
             Callback * const         cb)
    {
        assert(yout.size()==y.size());
        assert(yout.size()==k1.size());
        const size_t n  = yout.size(); prepare(n);
        const real_t hh = h * half;
        const real_t xh = x + hh;
        for(size_t i=n;i>0;--i) yt[i] = y[i] + hh * k1[i];
        if(cb) (*cb)(yt,xh);
        f(k2,xh,yt);

        for(size_t i=n;i>0;--i) yt[i] = y[i] + hh * k2[i];
        if(cb) (*cb)(yt,xh);
        f(k3,xh,yt);

        for(size_t i=n;i>0;--i) yt[i] = y[i] + h  * k3[i];
        const real_t xnew = x+h;
        if(cb) (*cb)(yt,xnew);
        f(k4,xnew,yt);

        for(size_t i=n;i>0;--i)
        {
            xadd.ldz();
            const real_t _1 = k1[i];
            const real_t _2 = k2[i];
            const real_t _3 = k3[i];
            const real_t _4 = k4[i];
            xadd << _1 << _2 << _2 << _3 << _3 << _4;
            yout[i] = y[i] + h * ( xadd.sum()/six );
        }
        if(cb) (*cb)(yout,xnew);

    }

    Vector<real_t>          yt;
    Vector<real_t>          k2;
    Vector<real_t>          k3;
    Vector<real_t>          k4;
    Cameo::Addition<real_t> xadd;
    const real_t            zero;
    const real_t            half;
    const real_t            six;

private:
    Y_Disable_Copy_And_Assign(Code);
    inline void prepare(const size_t n)
    {
        yt.adjust(n,zero);
        k2.adjust(n,zero);
        k3.adjust(n,zero);
        k4.adjust(n,zero);
    }
};


template <>
RK4<real_t>:: RK4(const size_t nmax) : code( new Code(nmax) )
{
}


template <>
RK4<real_t>:: ~RK4() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
void RK4<real_t>:: operator()(Writable<real_t> &       yout,
                              const Readable<real_t> & y,
                              const Readable<real_t> & dydx,
                              const real_t             x,
                              const real_t             h,
                              Equation &               f,
                              Callback * const         cb)
{
    assert(code);
    code->run(yout,y,dydx,x,h,f,cb);
}
