
template <>
class Optimizer<real_t>:: Code : public Object
{
public:
    typedef typename FCPU<real_t>::Type fcpu_t;
    typedef Field::In1D<real_t>         FieldType;

    inline explicit Code() :
    Object(),
    pmin(-(Numeric<real_t>::DIG+1)),
    pmax( Numeric<real_t>::MAX_10_EXP),
    pini(pmin/2),
    ffmt( new Field::Layout1D(pmin,pmax) ),
    lam("lambda",ffmt),
    step(),
    lu()
    {

        static const fcpu_t ten = 10;

        std::cerr << "pmin=" << pmin << "; pmax=" << pmax << " =>" << ffmt << std::endl;
        for(int p=pmin+1;p<=pmax;++p)
        {
            const fcpu_t l = std::pow(ten,p);
            Coerce(lam[p]) = l;
        }


    }

    inline virtual ~Code() noexcept
    {
    }

    const int        pmin;
    const int        pmax;
    const int        pini;
    Field::Format1D  ffmt;
    const FieldType  lam;
    Vector<real_t>   step;
    LU<real_t>       lu;


private:
    Y_Disable_Copy_And_Assign(Code);

};


template <>
Optimizer<real_t>:: Optimizer() : code( new Code() )
{
}

template <>
Optimizer<real_t>:: ~Optimizer() noexcept
{
    assert(code);
    Destroy(code);
}
