template <>
class CashKarp<real_t>:: Code : public Object
{
public:

    inline explicit Code() :
    Object(),
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
        static const real_t b51 = -11.0/54.0, b52=2.5,b53 = -70.0/27.0,b54=35.0/27.0;
        static const real_t b61=1631.0/55296.0,b62=175.0/512.0,b63=575.0/13824.0, b64=44275.0/110592.0,b65=253.0/4096.0;
        static const real_t c1=37.0/378.0,c3=250.0/621.0,c4=125.0/594.0,c6=512.0/1771.0;
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

        FOREACH_I ytemp[i]=y[i]+h*(b31*dydx[i]+b32*ak2[i]);
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
