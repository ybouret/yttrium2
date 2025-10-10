
template <>
class Eigen:: Jacobi<real_t>:: Code : public Object
{
public:

    inline explicit Code() : a(), b(), z(), xadd(), zero(0), one(1), fifth(0.2), half(0.5), hundred(100)
    {

    }

    inline virtual ~Code() noexcept
    {
    }

    Matrix<real_t>          a;
    Vector<real_t>          b,z;
    Cameo::Addition<real_t> xadd;
    const real_t            zero;
    const real_t            one;
    const real_t            fifth;
    const real_t            half;
    const real_t            hundred;


    static inline void Rotate(Matrix<real_t> &a,
                              const real_t    s,
                              const real_t    tau,
                              const size_t i,
                              const size_t j,
                              const size_t k,
                              const size_t l)
    {
        const real_t g=a[i][j];
        const real_t h=a[k][l];
        a[i][j]=g-s*(h+g*tau);
        a[k][l]=h+s*(g-h*tau);
    }

    inline bool run(Matrix<real_t> &v, Writable<real_t> &d, const Matrix<real_t> &a0)
    {
        assert(a0.isSquare());
        assert(v.gotSameMetricsThan(a0));
        assert(d.size() == a0.rows );

        // initialize
        const size_t n = a0.rows; prepare(n);
        const real_t n2 = n*n;
        for(size_t i=n;i>0;--i)
        {
            for(size_t j=n;j>0;--j)
            {
                a[i][j] = a0[i][j];
                v[i][j] = zero;
            }
            v[i][i] = one;
            b[i]    = d[i] = a[i][i];
            z[i]    = zero;
        }

        // loop
        for(size_t i=1;i<=128;++i)
        {
            xadd.ldz();
            for(size_t ip=1;ip<n;++ip)
                for(size_t iq=ip+1;iq<=n;++iq)
                    xadd << Fabs<real_t>::Of(a[ip][iq]);
            const real_t sm = xadd.sum();
            if( Fabs<real_t>::Of(sm) <= zero ) return true;

            const real_t tresh = (i<4) ? fifth * sm / n2 : zero;
            for(size_t ip=1;ip<=n-1;++ip)
            {
                for(size_t iq=ip+1;iq<=n;++iq)
                {
                    const real_t g = hundred*Fabs<real_t>::Of(a[ip][iq]);
                    if (i > 4 && (float)(fabs(d[ip])+g) == (float)fabs(d[ip])
                        && (float)(fabs(d[iq])+g) == (float)fabs(d[iq]))
                        a[ip][iq]=zero;
                    else if (fabs(a[ip][iq]) > tresh) {
                        real_t h = d[iq]-d[ip];
                        real_t t = zero;
                        if ((float)(fabs(h)+g) == (float)fabs(h))
                            t=(a[ip][iq])/h; //t = 1/(2θ)
                        else {
                            const real_t theta=0.5*h/(a[ip][iq]); //Equation (11.1.10).
                            t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
                            if (theta < 0.0) t = -t;
                        }
                        const real_t c=1.0/sqrt(1+t*t);
                        const real_t s=t*c;
                        const real_t tau=s/(1.0+c);
                        h=t*a[ip][iq];
                        z[ip] -= h;
                        z[iq] += h;
                        d[ip] -= h;
                        d[iq] += h;
                        a[ip][iq]=zero;
                        for(size_t j=1;j<ip;++j)    Rotate(a,s,tau,j,ip,j,iq);
                        for(size_t j=ip+1;j<iq;++j) Rotate(a,s,tau,ip,j,j,iq);
                        for(size_t j=iq+1;j<=n;++j) Rotate(a,s,tau,ip,j,iq,j);
                        for(size_t j=1;j<=n;++j)    Rotate(v,s,tau,j,ip,j,iq);
                    }
                }
            }
        }

        // too many iterations
        return false;
    }

private:
    Y_Disable_Copy_And_Assign(Code);

    inline void prepare(const size_t n)
    {
        a.make(n,n);
        b.adjust(n,zero);
        z.adjust(n,zero);
    }
};

template <>
Eigen:: Jacobi<real_t>:: Jacobi() : code( new Code() )
{
}


template <>
Eigen:: Jacobi<real_t>:: ~Jacobi() noexcept
{
    assert(code);
    Destroy(code);
}

template <>
bool Eigen:: Jacobi<real_t>:: operator()(Matrix<real_t> &v, Writable<real_t> &d, const Matrix<real_t> &a)
{
    assert(code);
    return code->run(v,d,a);
}
