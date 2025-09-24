template <>
class CashKarp<real_t>:: Code : public Object
{
public:

    inline explicit Code() : Object()
    {
    }

    inline virtual ~Code() noexcept
    {
    }



private:
    Y_Disable_Copy_And_Assign(Code);
};


template <>
CashKarp<real_t>:: CashKarp() : code( new Code() )
{
}


template <>
CashKarp<real_t>:: ~CashKarp() noexcept
{
    assert(code);
    Destroy(code);
}
