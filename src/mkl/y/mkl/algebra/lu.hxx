
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
bool LU<real_t>:: build(Matrix<real_t> &a)
{
    assert( a.isSquare() );
    const size_t n = a.rows; if( n <= 0 ) return false;
    if(!code)
    {
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
    return code->build(a);
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
