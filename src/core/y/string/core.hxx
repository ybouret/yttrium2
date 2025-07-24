
template <>
String<CH>:: ~String() noexcept
{
    assert(0!=code);
    Destroy(code);
}

template <>
String<CH>:: String() :
Y_String(),
code( new Code(0) )
{
}

template <>
String<CH>:: String(const String &other) :
Y_String(),
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
void String<CH>:: swapFor(String &other) noexcept
{
    CoerceSwap(code,other.code);
}



template <>
String<CH>:: String(const CH * const text) :
Y_String(),
code( 0 )
{
    const size_t tlen = StringLength(text);
    Coerce(code) = new Code(tlen);
    memcpy(code->base,text,(code->size=tlen)*sizeof(CH));
    assert(code->isValid());
}

template <>
String<CH>:: String(const CH * const text, const size_t tlen) :
Y_String(),
code( new Code(tlen) )
{
    assert( Good(text,tlen) );
    memcpy(code->base,text,(code->size=tlen)*sizeof(CH));
    assert(code->isValid());
}

template <>
String<CH>:: String(const CH c) :
Y_String(),
code( new Code(1) )
{
    code->base[0] = c;
    code->size    = 1;
    assert(code->isValid());
}


template <>
String<CH>::String(const CH * const lhs, const size_t lhsSize,
                   const CH * const rhs, const size_t rhsSize) :
Y_String(),
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
    return Sorting::AreDifferent(lhs.code->base, lhs.code->size,
                                 rhs.code->base, rhs.code->size);
}



template <>
bool operator!=<CH>(const String<CH> &lhs, const CH * const rhs) noexcept
{
    return Sorting::AreDifferent(lhs.code->base, lhs.code->size,
                                 rhs, StringLength(rhs));
}

template <>
bool operator!=<CH>(const CH * const lhs, const String<CH> &rhs) noexcept
{
    return Sorting::AreDifferent(lhs, StringLength(lhs),
                                 rhs.code->base, rhs.code->size);
}

template <>
bool operator!=<CH>(const String<CH> &lhs, const CH rhs) noexcept
{
    return Sorting::AreDifferent(lhs.code->base, lhs.code->size,
                                 &rhs, 1);
}

template <>
bool operator!=<CH>(const CH lhs, const String<CH> &rhs) noexcept
{
    return Sorting::AreDifferent(&lhs, 1,
                                 rhs.code->base, rhs.code->size);
}


template <>
SignType  String<CH>:: Compare(const String &lhs, const String &rhs) noexcept
{
    return Sorting::Lexicographic(lhs.code->base, lhs.code->size, rhs.code->base, rhs.code->size);
}

template<>
const CH & String<CH>:: getItemAt(const size_t indx) const noexcept
{
    assert(0!=code);
    assert(indx>0);
    assert(indx<=code->size);
    return code->item[indx];
}

template <>
size_t String<CH>:: serialize(OutputStream &fp) const
{
    assert(0!=code);
    size_t     num = code->size;
    size_t     res = fp.emitVBR(num);
    const CH * ptr = code->base;
    while(num-- > 0 ) {
        res += fp.emitCBR(*(ptr++));
    }
    return res;
}

template <>
String<CH>:: String(InputStream &      fp,
                    const char * const var) :
Y_String(),
code(0)
{
    // make full variable name in uid
    char              uid[256] = "String.size";

    if(var)
    {
        memset(uid,0,sizeof(uid));
        Core::Text::Copy(uid,sizeof(uid),var);
        Core::Text::Add(uid,sizeof(uid),".size");
    }

    // read variable size
    const size_t numChars = fp.readVBR<size_t>(uid);
    Coerce(code) = new Code(numChars);
    try {
        for(code->size=0;code->size<numChars;++code->size)
        {
            assert(code->isValid());
            if( 1 != fp.readCBR(code->base[code->size]) )
            {
                const size_t cidx = code->size+1;
                Specific::Exception excp("String(InputStream)","missing char %s/%s",
                                         Decimal(cidx).c_str(),
                                         Decimal(numChars).c_str());
                if(var) excp.add(" for %s", var);
                throw excp;
            }
        }
        assert(code->isValid());
    }
    catch(...)
    {
        Destroy(code);
        throw;
    }
}

template <>
void String<CH>:: free() noexcept
{
    assert(0!=code);
    code->erase();
}


template <>
size_t String<CH>:: available() const noexcept
{
    assert(0!=code);
    assert(code->isValid());
    return code->capacity - code->size;
}

template <>
void String<CH>:: pushTail(ParamType c)
{
    pushAtTail(c);
}

template <>
void String<CH>:: pushHead(ParamType c)
{
    pushAtHead(c);
}


template <>
void String<CH>:: popTail() noexcept
{
    assert(0!=code);
    assert(code->size>0);
    code->popTail();
}


template <>
void String<CH>:: popHead() noexcept
{
    assert(0!=code);
    assert(code->size>0);
    code->popHead();
}

template <>
const CH & String<CH>:: getHead() const noexcept
{
    assert(0!=code);
    assert(code->size>0);
    assert(code->base);
    return code->base[0];
}


template <>
const CH & String<CH>:: getTail() const noexcept
{
    assert(0!=code);
    assert(code->size>0);
    assert(code->item);
    return code->item[code->size];
}

template <>
void String<CH>:: reserve(const size_t n)
{
    assert(0!=code);
    if(n>0)
    {
        Code * const temp = new Code( code->capacity + n );
        while(temp->size<code->size)
        {
            temp->base[temp->size] = code->base[temp->size];
            code->base[temp->size] = 0;
            ++temp->size;
        }
        Destroy(code);
        Coerce(code) = temp;
    }
}

template <>
String<CH>:: String(const WithAtLeast_ &, const size_t n, const bool filled) :
Y_String(), code( new Code(n) )
{
    if(filled) code->size = n;
}

template <>
String<CH> & String<CH>:: reverse() noexcept
{
    assert(0!=code);
    Algorithm::Reverse(code->base,code->size,Swap<CH>);
    return *this;
}

template <>
const void * String<CH>:: ro() const noexcept { assert(code); return code->base; }


template <>
size_t String<CH>:: length() const noexcept { assert(code); return code->size; }


