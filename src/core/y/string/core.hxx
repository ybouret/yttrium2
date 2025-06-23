
template <>
String<CH>:: ~String() noexcept
{
    assert(0!=code);
    Destroy(code);
}

template <>
String<CH>:: String() :
code( new Code(0) )
{
}

template <>
String<CH>:: String(const String &other) :
code( new Code(*other.code) )
{

}

template <>
size_t String<CH>:: size() const noexcept
{
    assert(0!=code);
    return code->size;
}

template <>
size_t String<CH>:: capacity() const noexcept
{
    assert(0!=code);
    return code->capacity;
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

    // assign otherwise
    code->assign(other.code->base,other.code->size);

    return *this;
}




template <>
String<CH>:: String(const CH * const text) : code( 0 )
{
    const size_t tlen = StringLength(text);
    Coerce(code) = new Code(tlen);
    memcpy(code->base,text,(code->size=tlen)*sizeof(CH));
    assert(code->isValid());
}

template <>
String<CH>:: String(const CH * const text, const size_t tlen) : code( new Code(tlen) )
{
    assert( Good(text,tlen) );
    memcpy(code->base,text,(code->size=tlen)*sizeof(CH));
    assert(code->isValid());
}

template <>
String<CH>:: String(const CH c) : code( new Code(1) )
{
    code->base[0] = c;
    code->size    = 1;
    assert(code->isValid());
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
    assert(code->isValid());
}

template <>
const char * String<CH>:: c_str() const noexcept
{
    assert(0!=code);
    static const IntToType< IsSameType<CH,char>::Value > choice = {};
    return code->asChar(choice);
}

template <>
String<CH> & String<CH>:: operator=(const CH * const text)
{

    // get length
    const size_t tlen = StringLength(text);

    // copy/swap if length is too high
    if(code->capacity<tlen)
    {
        String temp(text,tlen);
        CoerceSwap(code,temp.code);
        return *this;
    }

    // assign otherwise
    code->assign(text,tlen);


    return *this;
}

template <>
String<CH> & String<CH>:: operator=(const CH c) noexcept
{
    code->assign(&c,1);
    return *this;
}

template <>
String<CH> & String<CH>::pushAtTail(const CH *const text, const size_t tlen)
{
    assert( Good(text,tlen) );

    const size_t mlen = code->size;
    const size_t sum  = mlen + tlen;
    if( sum > code->capacity )
    {
        Code * temp = new Code(sum);
        memcpy(temp->base,      code->base, mlen*sizeof(CH));
        memcpy(temp->base+mlen, text,       tlen*sizeof(CH));
        temp->size = sum;
        delete code;
        Coerce(code) = temp;
        return *this;
    }

    // code pushTail
    code->pushTail(text,tlen);
    return *this;
}

template <>
String<CH> & String<CH>::pushAtTail(const CH *const text)
{
    return pushAtTail(text, StringLength(text) );
}

template <>
String<CH> & String<CH>::pushAtTail(const CH c)
{
    return pushAtTail(&c,1);
}


template <>
String<CH> & String<CH>::pushAtTail(const String &s)
{
    return pushAtTail(s.code->base, s.code->size );
}



template <>
String<CH> & String<CH>::pushAtHead(const CH *const text, const size_t tlen)
{
    assert( Good(text,tlen) );

    const size_t mlen = code->size;
    const size_t sum  = mlen + tlen;
    if( sum > code->capacity )
    {
        Code * temp = new Code(sum);
        memcpy(temp->base,      text,       tlen*sizeof(CH));
        memcpy(temp->base+tlen, code->base, mlen*sizeof(CH));
        temp->size = sum;
        delete code;
        Coerce(code) = temp;
        return *this;
    }

    // code pushHed
    code->pushHead(text,tlen);
    return *this;
}


template <>
String<CH> & String<CH>:: pushAtHead(const CH *const text)
{
    return pushAtHead(text, StringLength(text) );
}

template <>
String<CH> & String<CH>:: pushAtHead(const CH c)
{
    return pushAtHead(&c,1);
}


template <>
String<CH> & String<CH>:: pushAtHead(const String &s)
{
    return pushAtHead(s.code->base, s.code->size );
}




template <>
String<CH> operator+<CH>(const String<CH> &lhs, const String<CH> &rhs)
{
    return String<CH>(lhs.code->base,lhs.code->size,
                      rhs.code->base,rhs.code->size);
}


template <>
String<CH> operator+<CH>(const String<CH> &lhs, const CH * const rhs)
{
    return String<CH>(lhs.code->base,lhs.code->size,
                      rhs,StringLength(rhs));
}

template <>
String<CH> operator+<CH>(const CH * const lhs, const String<CH> &rhs)
{
    return String<CH>(lhs,StringLength(lhs),
                      rhs.code->base,rhs.code->size);
}

template <>
String<CH> operator+<CH>(const String<CH> &lhs, const CH rhs)
{
    return String<CH>(lhs.code->base,lhs.code->size,
                      &rhs,1);
}

template <>
String<CH> operator+<CH>(const CH lhs, const String<CH> &rhs)
{
    return String<CH>(&lhs,1,
                      rhs.code->base,rhs.code->size);
}

// equality

template <>
bool operator==<CH>(const String<CH> &lhs, const String<CH> &rhs) noexcept
{
    return Sorting::AreEqual(lhs.code->base, lhs.code->size,
                             rhs.code->base, rhs.code->size);
}

template <>
bool operator==<CH>(const String<CH> &lhs, const CH * const rhs) noexcept
{
    return Sorting::AreEqual(lhs.code->base, lhs.code->size,
                             rhs, StringLength(rhs));
}

template <>
bool operator==<CH>(const CH * const lhs, const String<CH> &rhs) noexcept
{
    return Sorting::AreEqual(lhs, StringLength(lhs),
                             rhs.code->base, rhs.code->size);
}

template <>
bool operator==<CH>(const String<CH> &lhs, const CH rhs) noexcept
{
    return Sorting::AreEqual(lhs.code->base, lhs.code->size,
                             &rhs, 1);
}

template <>
bool operator==<CH>(const CH lhs, const String<CH> &rhs) noexcept
{
    return Sorting::AreEqual(&lhs, 1,
                             rhs.code->base, rhs.code->size);
}



// differenct

template <>
bool operator!=<CH>(const String<CH> &lhs, const String<CH> &rhs) noexcept
{
    return StringAreDifferent(lhs.code->base, lhs.code->size,
                              rhs.code->base, rhs.code->size);
}



template <>
bool operator!=<CH>(const String<CH> &lhs, const CH * const rhs) noexcept
{
    return StringAreDifferent(lhs.code->base, lhs.code->size,
                              rhs, StringLength(rhs));
}

template <>
bool operator!=<CH>(const CH * const lhs, const String<CH> &rhs) noexcept
{
    return StringAreDifferent(lhs, StringLength(lhs),
                              rhs.code->base, rhs.code->size);
}

template <>
bool operator!=<CH>(const String<CH> &lhs, const CH rhs) noexcept
{
    return StringAreDifferent(lhs.code->base, lhs.code->size,
                              &rhs, 1);
}

template <>
bool operator!=<CH>(const CH lhs, const String<CH> &rhs) noexcept
{
    return StringAreDifferent(&lhs, 1,
                              rhs.code->base, rhs.code->size);
}
