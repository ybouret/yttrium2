
#if 0
template <>
String<CH>:: ~String() noexcept
{
    assert(0!=code);
    Destroy(code);
}

template <>
String<CH>:: String() : code( new Code(0) )
{
}

template <>
String<CH>:: String(const String &other) :
code( new Code(*other.code) )
{

}


template <>
String<CH> & String<CH>:: operator=( const String &other )
{

    // nothing on self assign
    if(this == &other)
        return *this;

    // copy/swap on bigger other
    if(code->capacity<other.code->size) {
        String temp(other);
        CoerceSwap(code,temp.code);
        return *this;
    }

    // copy otherwise
    code->copy(*other.code);

    return *this;
}


template <>
String<CH>:: String(const CH * const text) : code(0)
{
    const size_t length = StringLength(text);
    Coerce(code) = new Code( length );
    memcpy(code->base,text,(code->size=length)*sizeof(CH));
}

template <>
String<CH>:: String(const CH * const text, const size_t tlen) : code( new Code(tlen) )
{
    assert( Good(text,tlen) );
    memcpy(code->base,text,(code->size=tlen)*sizeof(CH));
    assert(code->checked());
}

template <>
String<CH>::String(const CH * const lhs, const size_t lhsSize,
                   const CH * const rhs, const size_t rhsSize) :
code( 0 )
{
    const size_t sum = lhsSize + rhsSize;
    Coerce(code)     = new Code(sum);
    assert( Good(lhs,lhsSize) );
    assert( Good(rhs,rhsSize) );
    memcpy(code->base,         lhs, lhsSize*sizeof(CH));
    memcpy(code->base+lhsSize, rhs, rhsSize*sizeof(CH));
    code->size = sum;
    assert(code->checked());
}
#endif
