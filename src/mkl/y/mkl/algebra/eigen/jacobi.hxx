
template <>
class Eigen:: Jacobi<real_t>:: Code : public Object
{
public:

    inline explicit Code() : b(), z(), zero(0)
    {

    }

    inline virtual ~Code() noexcept
    {
    }

    Vector<real_t> b,z;
    const real_t   zero;

private:
    Y_Disable_Copy_And_Assign(Code);

    inline void prepare(const size_t n)
    {
        b.adjust(n,zero);
        z.adjust(n,zero);
    }
};

template <>
Eigen:: Jacobi<real_t>:: Jacobi() : code( new Code() )
{
}


template <>
Eigen:: Jacobi<real_t>:: ~Jacobi() noexcept
{
    assert(code);
    Destroy(code);
}
