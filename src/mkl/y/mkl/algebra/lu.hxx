
template <>
LU<real_t>:: LU(const size_t maxDim) :
code( maxDim > 0 ? new Code(maxDim) : 0)
{
}


template <>
void LU<real_t>:: release_() noexcept
{
    if(code) { delete code; code=0; }
}

template <>
void LU<real_t>:: release() noexcept
{
    release_();
}

template <>
LU<real_t>:: ~LU() noexcept
{
    release_();
}

template <>
LU<real_t> & LU<real_t>:: make(const size_t n)
{
    if(!code)
    {
        if(n>0)
            code = new Code(n);
    }
    else
    {
        if(code->dims<n)
        {
            release_();
            code = new Code(n);
        }
    }
    assert(code->dims>=n);
    return *this;
}

template <>
bool LU<real_t>:: build(Matrix<real_t> &a)
{
    assert( a.isSquare() );
    const size_t n = a.rows; if( n <= 0 ) return false;
    return make(n).code->build(a);
}

template <>
real_t LU<real_t>:: det(const Matrix<real_t> &a)
{
    assert( a.isSquare() );
    const size_t n = a.rows; if( n <= 0 ) return static_cast<real_t>(0);
    assert(0!=code);
    assert(code->dims>=n);
    return code->det(a);
}


template <>
size_t LU<real_t>:: size() const noexcept
{
    return code ? code->dims : 0;
}

template <>
void LU<real_t>:: solve(const Matrix<real_t> &a, Writable<real_t> &b)
{
    assert( a.isSquare() );
    assert( a.rows>0 );
    assert( a.rows==b.size() );
    assert( 0 != code);
    assert( code->dims >= a.rows );
    code->solve(a,b);
}

template <>
void  LU<real_t>:: inv(const Matrix<real_t> &a, Matrix<real_t> &ia)
{
    assert( a.isSquare() );
    assert( a.rows>0 );
    assert( 0 != code);
    assert( code->dims >= a.rows );
    assert(a.gotSameMetricsThan(ia));
    code->inv(a,ia);
}

 
template <>
void LU<real_t>:: solve(const Matrix<real_t> &a, Matrix<real_t> &rhs, Writable<real_t> &tmp)
{
    assert( a.isSquare() );
    assert( a.rows>0 );
    assert( a.rows==tmp.size() );
    assert( a.rows==rhs.rows   );
    assert( 0 != code);
    assert( code->dims >= a.rows );
    code->solve(a,rhs,tmp);
}
