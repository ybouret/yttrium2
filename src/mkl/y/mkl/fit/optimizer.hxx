
template <>
class Optimizer<real_t>:: Code : public Object
{
public:
    inline explicit Code() :
    Object(),
    pmin(-(Numeric<real_t>::DIG+1)),
    pmax( Numeric<real_t>::MAX_10_EXP),
    ffmt( new Field::Layout1D(pmin,pmax) ),
    lam("lambda",ffmt),
    step(),
    lu()
    {

        std::cerr << "pmin=" << pmin << "; pmax=" << pmax << " =>" << ffmt << std::endl;
    }

    inline virtual ~Code() noexcept
    {
    }
    
    const int       pmin;
    const int       pmax;
    Field::Format1D ffmt;
    const Field::In1D<real_t>  lam;
    Vector<real_t>  step;
    LU<real_t>      lu;


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
