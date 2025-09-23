
template <>
class Eigen:: Hessenberg<real_t>:: Code : public Object
{
public:
    inline explicit Code() : zero(0) {}
    inline virtual ~Code() noexcept {}

    inline void run(Matrix<real_t> &a)
    {
        assert(a.isSquare());
        const size_t n = a.rows;
        real_t y;

        for (size_t m=2;m<n;m++)
        {

            real_t pivot=0;
            bool   found=false;
            {
                size_t i=m;
                for (size_t j=m;j<=n;j++)
                {
                    if (fabs(a[j][m-1]) > fabs(pivot))
                    {
                        pivot=a[j][m-1];
                        found=true;
                        i=j;
                    }
                }
                if (i != m)
                {
                    for (size_t j=m-1;j<=n;j++) Swap(a[i][j],a[m][j]);
                    for (size_t j=1;j<=n;j++)   Swap(a[j][i],a[j][m]);
                }
            }


            if (found) {
                for (size_t i=m+1;i<=n;i++) {
                    if ((y=a[i][m-1]) != 0.0) {
                        y /= pivot;
                        a[i][m-1]=y;
                        for (size_t j=m;j<=n;j++) a[i][j] -= y*a[m][j];
                        for (size_t j=1;j<=n;j++) a[j][m] += y*a[j][i];
                    }
                }
            }
        }

        // cleanup to Hessenberg final form
        for(size_t j=1;j<=n;++j)
        {
            for(size_t i=j+2;i<=n;++i) a[i][j] = zero;
        }

    }

    const real_t zero;

private:
    Y_Disable_Copy_And_Assign(Code);
};

template <>
Eigen:: Hessenberg<real_t>:: Hessenberg() : code( new Code() )
{
}


template <>
Eigen:: Hessenberg<real_t>:: ~Hessenberg() noexcept
{
    assert(0!=code);
    Destroy(code);
}

template <>
void Eigen:: Hessenberg<real_t>:: operator()(Matrix<real_t> &a)
{
    assert(0!=code);
    code->run(a);
}

