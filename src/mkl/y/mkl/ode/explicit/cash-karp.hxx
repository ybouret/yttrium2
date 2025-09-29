template <>
class CashKarp<real_t>:: Code : public Object
{
public:

    inline explicit Code() :
    Object(),
    ak2(),
    ak3(),
    ak4(),
    ak5(),
    ak6(),
    ytemp(),
    xadd(),
    zero(0)
    {
    }

    inline virtual ~Code() noexcept
    {
    }

    inline void run(Writable<real_t> &       yout,
                    Writable<real_t> &       yerr,
                    const Readable<real_t> & y,
                    const Readable<real_t> & dydx,
                    const real_t             x,
                    const real_t             h,
                    Equation               & f,
                    Callback * const         cb)
    {
        static const real_t
        a2 = REAL(0.2),
        a3 = REAL(0.3),
        a4 = REAL(0.6),
        a5 = REAL(1.0),
        a6 = REAL(0.875);

        static const real_t b21=REAL(0.2);

        static const real_t
        b31 = REAL(3.0)/REAL(40.0),
        b32 = REAL(9.0)/REAL(40.0);

        static const real_t
        b41 = REAL(0.3),
        b42 = REAL(-0.9),
        b43 = REAL(1.2);

        static const real_t
        b51 = REAL(-11.0)/REAL(54.0),
        b52 = REAL(2.5),
        b53 = REAL(-70.0)/REAL(27.0),
        b54 = REAL(35.0)/REAL(27.0);
        
        static const real_t
        b61=REAL(1631.0)/REAL(55296.0),
        b62=REAL(175.0)/REAL(512.0),
        b63=REAL(575.0)/REAL(13824.0),
        b64=REAL(44275.0)/REAL(110592.0),
        b65=REAL(253.0)/REAL(4096.0);

        static const real_t
        c1=REAL(37.0) /REAL(378.0),
        c3=REAL(250.0)/REAL(621.0),
        c4=REAL(125.0)/REAL(594.0),
        c6=REAL(512.0)/REAL(1771.0);
        
        static const real_t
        dc1 = c1-REAL(2825.0)/REAL(27648.0),
        dc3 = c3-REAL(18575.0)/REAL(48384.0),
        dc4 = c4-REAL(13525.0)/REAL(55296.0),
        dc5 = REAL(-277.00)/REAL(14336.0),
        dc6 = c6-REAL(0.25);

        const size_t n = y.size(); prepare(n);

        {
            const real_t h21 = h * b21;
            FOREACH_I ytemp[i]=y[i]+h21*dydx[i];
        }
        FieldType::Compute(f,ak2,x+a2*h,ytemp,cb); //(*derivs)(x+a2*h,ytemp,ak2);

        FOREACH_I
        {
            //ytemp[i]=y[i]+h*(b31*dydx[i]+b32*ak2[i]);
            const real_t h31 = h*b31;
            const real_t h32 = h*b32;
            xadd = y[i];
            xadd += h31 * dydx[i];
            xadd += h32 * ak2[i];
            ytemp[i] = xadd.sum();
        }
        FieldType::Compute(f,ak3,x+a3*h,ytemp,cb); //(*derivs)(x+a3*h,ytemp,ak3);

        FOREACH_I ytemp[i]=y[i]+h*(b41*dydx[i]+b42*ak2[i]+b43*ak3[i]);
        FieldType::Compute(f,ak4,x+a4*h,ytemp,cb); //(*derivs)(x+a4*h,ytemp,ak4);

        FOREACH_I ytemp[i]=y[i]+h*(b51*dydx[i]+b52*ak2[i]+b53*ak3[i]+b54*ak4[i]);
        FieldType::Compute(f,ak5,x+a5*h,ytemp,cb);//(*derivs)(x+a5*h,ytemp,ak5);

        FOREACH_I ytemp[i]=y[i]+h*(b61*dydx[i]+b62*ak2[i]+b63*ak3[i]+b64*ak4[i]+b65*ak5[i]);
        FieldType::Compute(f,ak6,x+a6*h,ytemp,cb); //(*derivs)(x+a6*h,ytemp,ak6);

        FOREACH_I yout[i]=y[i]+h*(c1*dydx[i]+c3*ak3[i]+c4*ak4[i]+c6*ak6[i]);
        FOREACH_I yerr[i]=h*(dc1*dydx[i]+dc3*ak3[i]+dc4*ak4[i]+dc5*ak5[i]+dc6*ak6[i]);


    }


    Vector<real_t> ak2,ak3,ak4,ak5,ak6,ytemp;
    Cameo::Addition<real_t> xadd;
    const real_t            zero;

private:
    Y_Disable_Copy_And_Assign(Code);
    inline void prepare(const size_t n)
    {
        ak2.adjust(n,zero);
        ak3.adjust(n,zero);
        ak4.adjust(n,zero);
        ak5.adjust(n,zero);
        ak6.adjust(n,zero);
        ytemp.adjust(n,zero);
    }
};


template <>
CashKarp<real_t>:: CashKarp() : code( new Code() )
{
}


template <>
CashKarp<real_t>:: ~CashKarp() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
const char * CashKarp<real_t>:: callSign() const noexcept
{
    return CaskKarpID;
}

template <>
void CashKarp<real_t>:: operator()(Writable<real_t> &       yout,
                                   Writable<real_t> &       yerr,
                                   const Readable<real_t> & y,
                                   const Readable<real_t> & dydx,
                                   const real_t             x,
                                   const real_t             h,
                                   Equation               & f,
                                   Callback * const         cb)
{
    assert(code);
    code->run(yout, yerr, y, dydx, x, h, f, cb);
}
