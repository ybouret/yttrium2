
template <>
class Optimizer<real_t>:: Code : public Object
{
public:
    inline explicit Code() :
    Object(),
    pmin(-Numeric<real_t>::DIG),
    step(),
    lu()
    {
    }

    inline virtual ~Code() noexcept
    {
    }

    const int      pmin;
    Vector<real_t> step;
    LU<real_t>     lu;


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
