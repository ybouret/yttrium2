
template <>
class Eigen::Balance<real_t>:: Code : public Object
{
public:
    inline explicit Code() :
    RADIX( FLT_RADIX ),
    SQRDX( RADIX * RADIX ),
    one(1),
    zero(0),
    safe( REAL(0.95) ),
    radd(),
    cadd()
    {
    }

    inline virtual ~Code() noexcept
    {
    }

    const real_t            RADIX; //!< numerical RADIX
    const real_t            SQRDX; //!< RADIX^2
    const real_t            one;   //!< 1
    const real_t            zero;  //!< 0
    const real_t            safe;  //!< 0.95
    Cameo::Addition<real_t> radd;  //!< for row norm
    Cameo::Addition<real_t> cadd;  //!< for col norm

    inline void run(Matrix<real_t> &a)
    {
        const size_t n = a.rows; assert( a.isSquare() );
        size_t last = 0;
        while(0 == last)
        {
            last = 1;
            for (size_t i=1;i<=n;i++) {
                radd.ldz();
                cadd.ldz();
                for (size_t j=n;j>0;--j)
                {
                    if (j != i) {
                        cadd += Fabs<real_t>::Of(a[j][i]);
                        radd += Fabs<real_t>::Of(a[i][j]);
                    }
                }
                const real_t r = radd.sum();
                real_t       c = cadd.sum();
                if (c>zero && r>zero)
                {
                    real_t g=r/RADIX;
                    real_t f=one;
                    real_t s=c+r;
                    while (c<g) {
                        f *= RADIX;
                        c *= SQRDX;
                    }
                    g=r*RADIX;
                    while (c>g) {
                        f /= RADIX;
                        c /= SQRDX;
                    }
                    if( (c+r)/f < safe*s) {
                        last=0;
                        g=one/f;
                        for (size_t j=n;j>0;--j)  a[i][j] *= g;
                        for (size_t j=1;j<=n;++j) a[j][i] *= f;
                    }
                }
            }
        }

    }


private:
    Y_Disable_Copy_And_Assign(Code);
};

template <>
Eigen:: Balance<real_t>:: Balance() : code( new Code() )
{
}

template <>
Eigen:: Balance<real_t>:: ~Balance() noexcept
{
    Destroy(code);
}

template <>
void Eigen:: Balance<real_t>:: operator()(Matrix<real_t> &a)
{
    assert(0!=code);
    code->run(a);
}

