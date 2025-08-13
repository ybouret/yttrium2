
template <> SVD<real_t>:: SVD() : code( new Code() ) { }

template <> SVD<real_t>:: ~SVD() noexcept
{
    assert(0!=code);
    Destroy(code);
}

template <> bool SVD<real_t>::build(Matrix<real_t> &a, Writable<real_t> &w, Matrix<real_t> &v)
{
    assert(0!=code);
    return code->build(a,w,v);
}

template <>
void SVD<real_t>:: Sort(Matrix<real_t> &u, Writable<real_t> &d, Matrix<real_t> &v, Compare compare)
{
    assert(0!=compare);
    assert(v.rows==v.cols);
    assert(v.rows==d.size());
    assert(u.cols==d.size());

    const size_t n = d.size();
    for(size_t i=1;i<n;i++)
    {
        size_t k=i;
        real_t p=d[i];
        for(size_t j=i+1;j<=n;++j)
        {
            if( Negative == compare(d[j],p) )
                p = d[k=j];
        }

        if(k != i)
        {
            d[k]=d[i];
            d[i]=p;
            v.swapCols(k,i);
            u.swapCols(k,i);
        }
    }
}

static inline SignType CompareA_(const real_t &lhs, const real_t &rhs) noexcept
{
    const real_t l = Fabs<real_t>::Of(lhs);
    const real_t r = Fabs<real_t>::Of(rhs);
    return Sign::Of(l,r);
}

template <>
void SVD<real_t>:: Sort(Matrix<real_t> &u, Writable<real_t> &d, Matrix<real_t> &v)
{
    Sort(u,d,v,CompareA_);
}

template <>
void SVD<real_t>:: solve(const Matrix<real_t>    &u,
                         const Readable<real_t>  &w,
                         const Matrix<real_t>    &v,
                         const Readable<real_t>  &b,
                         Writable<real_t> &       x)
{
    assert(0!=code);
    code->solve(u,w,v,b,x);
}
