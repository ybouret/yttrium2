template <>
class DormandPrince<real_t>:: Code : public Object
{
public:
    typedef DormandPrince<real_t>::Equation Equation;
    typedef DormandPrince<real_t>::Callback Callback;

    Vector<real_t>          ak2,ak3,ak4,ak5,ak6,ak7,ytemp;
    Cameo::Addition<real_t> xadd;
    const real_t            zero;

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
        a6 = REAL(1.0),
        a7 = REAL(1.0);

        const size_t n = y.size(); prepare(n);

        {
            static const real_t a2 = REAL(0.2);
            FOREACH_I
            {
                static const real_t b21 = REAL(0.2);
                const        real_t h21 = h * b21;
                FOREACH_I ytemp[i]=y[i]+h21*dydx[i];
            }
            FieldType::Compute(f,ak2,x+a2*h,ytemp,cb);
        }

        {
            static const real_t a3 = REAL(0.3);
            static const real_t b31 = REAL(3.0)/REAL(40.0);
            static const real_t b32 = REAL(9.0)/REAL(40.0);
            FOREACH_I
            {
                xadd.ldz();
                xadd += b31 * dydx[i];
                xadd += b32 * ak2[i];
                ytemp[i] = y[i] + h * xadd.sum();
            }
            FieldType::Compute(f,ak3,x+a3*h,ytemp,cb);
        }

        {
            static const real_t a4  = REAL(0.8);
            static const real_t b41 = REAL(44.0)/REAL(45.0);
            static const real_t b42 = REAL(-56.0)/REAL(15.0);
            static const real_t b43 = REAL(32.0)/REAL(9.0);
            FOREACH_I
            {
                xadd.ldz();
                xadd += b41 * dydx[i];
                xadd += b42 * ak2[i];
                xadd += b43 * ak3[i];
                ytemp[i] = y[i] + h * xadd.sum();
            }
            FieldType::Compute(f,ak4,x+a4*h,ytemp,cb); //(*derivs)(x+a4*h,ytemp,ak4);
        }

        {
            static const real_t a5  = REAL(8.0)/REAL(9.0);
            static const real_t b51 = REAL(19372.0)/REAL(6561.0);
            static const real_t b52 = REAL(-25360.0)/REAL(2187.0);
            static const real_t b53 = REAL(64448.0)/REAL(6561.0);
            static const real_t b54 = REAL(-212.0)/REAL(729.0);
            
            FOREACH_I
            {
                //ytemp[i]=y[i]+h*(b51*dydx[i]+b52*ak2[i]+b53*ak3[i]+b54*ak4[i]);
                xadd.ldz();
                xadd += b51 * dydx[i];
                xadd += b52 * ak2[i];
                xadd += b53 * ak3[i];
                xadd += b54 * ak4[i];
                ytemp[i] = y[i] + h * xadd.sum();
            }
            FieldType::Compute(f,ak5,x+a5*h,ytemp,cb);
        }

        {
            static const real_t b61 = REAL(9017.0)/REAL(3168.0);;
            static const real_t b62 = REAL(-355.0)/REAL(33.0);
            static const real_t b63 = REAL(46732.0)/REAL(5247.0);
            static const real_t b64 = REAL(49.0)/REAL(176.0);
            static const real_t b65 = REAL(-5103.0)/REAL(18656.0);
            FOREACH_I
            {

                xadd.ldz();
                xadd += b61 * dydx[i];
                xadd += b62 * ak2[i];
                xadd += b63 * ak3[i];
                xadd += b64 * ak4[i];
                xadd += b65 * ak5[i];
                ytemp[i] = y[i] + h * xadd.sum();
            }
            FieldType::Compute(f,ak6,x+h,ytemp,cb);
        }

    }


private:
    Y_Disable_Copy_And_Assign(Code);

    inline void prepare(const size_t n)
    {
        ak2.adjust(n,zero);
        ak3.adjust(n,zero);
        ak4.adjust(n,zero);
        ak5.adjust(n,zero);
        ak6.adjust(n,zero);
        ak7.adjust(n,zero);
        ytemp.adjust(n,zero);
    }
};



template <>
const char * DormandPrince<real_t>:: callSign() const noexcept
{
    return DormandPrinceID;
}

template <>
void DormandPrince<real_t>:: operator()(Writable<real_t> &       yout,
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
