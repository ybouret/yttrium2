
template <>
ZFind<real_t>:: ZFind() noexcept : Identifiable() {}

template <>
ZFind<real_t>:: ~ZFind() noexcept {}


template <>
const char * ZFind<real_t>:: callSign() const noexcept { return ZFindCallSign; }


template <>
bool ZFind<real_t>:: found(Handle &hx, Handle &hf, Triplet<real_t> &x, Triplet<real_t> &f, FunctionType &F)
{
    const SignType sa = Sign::Of(f.a);
    const SignType sc = Sign::Of(f.c);
    switch( Sign::Pair(sa,sc) )
    {
        case Sign::ZZ:
            x.b = Half<real_t>::Of(x.a+x.c);
            f.b = F(x.b);
            if( __Zero__ != Sign::Of(f.b) ) throw Specific::Exception( callSign(), "found invalid initial middle point");
            return true;

        case Sign::ZN:
        case Sign::ZP:
            x.b = x.a;
            f.b = f.a;
            return true;

        case Sign::NZ:
        case Sign::PZ:
            x.b = x.c;
            f.b = f.c;
            return true;

        case Sign::NN:
        case Sign::PP:
            throw Specific::Exception(callSign(),"no initial opposite signs");

        case Sign::PN:
            hx.pos = &x.a; hf.pos = &f.a;
            hx.neg = &x.c; hf.neg = &f.c;
            break;

        case Sign::NP:
            hx.pos = &x.c; hf.pos = &f.c;
            hx.neg = &x.a; hf.neg = &f.a;
            break;

    }
    return false;
}
