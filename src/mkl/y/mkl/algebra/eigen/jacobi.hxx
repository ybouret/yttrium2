
template <>
class Eigen:: Jacobi<real_t>:: Code : public Object
{
public:

    inline explicit Code() : a(), b(), z(), xadd(), zero(0), one(1), fifth(0.2)
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

    inline void run(const Matrix<real_t> &a0, Matrix<real_t> &v, Writable<real_t> &d)
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
        for(size_t i=1;;++i)
        {
            xadd.ldz();
            for(size_t ip=1;ip<n;++ip)
                for(size_t iq=ip+1;iq<=n;++iq)
                    xadd << Fabs<real_t>::Of(a[ip][iq]);
            const real_t sm = xadd.sum();
            if( Fabs<real_t>::Of(sm) <= zero ) return;
            const real_t thres = (i<4) ? fifth * sm / n2 : zero;

            for(size_t ip=1;ip<=n-1;++ip)
            {
                for(size_t iq=ip+1;iq<=n;++iq)
                {

                }
            }
        }


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
