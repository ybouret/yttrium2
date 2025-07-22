
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/rational.hpp"
#include "y/mkl/complex.hpp"
#include "y/container/cxx/array.hpp"
#include "y/cameo/addition.hpp"
#include "y/cameo/multiplication.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class LU<T>:: Code : public Object
        {
        public:

            explicit Code(const size_t n) :
            Object(),
            dneg(false),
            dims(n),
            S1(1),
            xadd(),
            scal(dims),
            indx(dims),
            xmul()
            {
                assert(dims>0);
            }

            virtual ~Code() noexcept
            {
            }


            inline bool build(Matrix<T> &a)
            {
                assert(a.isSquare());
                assert(a.rows<=dims);
                const size_t n = a.rows; if(n<=0) return false;


                // initialize determinant sign
                dneg = false;

                // find scaling
                for(size_t i=n;i>0;--i)
                {
                    ScalarType apiv(0);
                    {
                        const Readable<T> &a_i = a[i];
                        for(size_t j=n;j>0;--j)
                        {
                            const ScalarType atmp = Fabs<T>::Of(a_i[j]);
                            if(atmp>apiv) apiv = atmp;
                        }
                    }
                    if( Sign::LEQZ(apiv) ) return false; // null row
                    scal[i] = S1/apiv;
                }

                // Crout's algorithm
                for(size_t j=1;j<=n;++j)
                {
                    for(size_t i=1;i<j;++i)
                    {
                        T sum=a[i][j];
                        for(size_t k=1;k<i;++k) sum -= a[i][k]*a[k][j];
                        a[i][j]=sum;
                    }

                    ScalarType apiv(0);
                    size_t     imax = 1;
                    for(size_t i=j;i<=n;++i) {
                        T sum=a[i][j];
                        for (size_t k=1;k<j;++k)
                            sum -= a[i][k]*a[k][j];
                        const ScalarType atmp = Fabs<T>::Of(a[i][j]=sum) * scal[i];
                        if(atmp>=apiv)
                        {
                            apiv = atmp;
                            imax = i;
                        }
                    }

                    if(j!=imax)
                    {
                        // permutation
                        a.swapRows(imax,j);
                        scal[imax] = scal[j];
                        dneg = !dneg;
                    }
                    indx[j] = imax;
                    {
                        const ScalarType aa = Fabs<T>::Of(a[j][j]);
                        if( Sign::LEQZ(aa) ) return false;
                    }

                    if (j != n)
                    {
                        ConstType &den = a[j][j];
                        for (size_t i=j+1;i<=n;++i)
                            a[i][j] /= den;
                    }
                }

                

                return true;
            }

            inline ConstType det(const Matrix<T> &a) 
            {
                assert(a.rows>0);
                assert(a.isSquare());
                assert(a.rows<=dims);
                const size_t n = a.rows;

                xmul = a[1][1];
                for(size_t i=n;i>1;--i)
                    xmul *= a[i][i];
                
                return dneg ? -xmul.product() : xmul.product();
            }

            inline void solve(const Matrix<T> &a, Writable<T> &b)
            {
                assert(a.rows>0);
                assert(a.isSquare());
                assert(a.rows<=dims);
                assert(a.rows==b.size());
                const size_t n  = a.rows;
                size_t       ii = 0;
                for(size_t i=1;i<=n;++i)
                {
                    const size_t ip=indx[i];
                    T sum=b[ip];
                    b[ip]=b[i];
                    if (ii)
                    {
                        for(size_t j=ii;j<=i-1;++j)
                            sum -= a[i][j]*b[j];
                    }
                    else
                    {
                        if( Sign::GTZ( Fabs<T>::Of(sum) ) )
                            ii=i;
                    }
                    b[i]=sum;
                }

                for(size_t i=n;i>=1;--i)
                {
                    T sum=b[i];
                    for(size_t j=i+1;j<=n;++j)
                        sum -= a[i][j]*b[j];
                    b[i]=sum/a[i][i];
                }
            }


            bool                        dneg;
            const size_t                dims;
            const ScalarType            S1;
            Cameo::Addition<Type>       xadd;
            CxxArray<ScalarType>        scal;
            CxxArray<size_t>            indx;
            Cameo::Multiplication<Type> xmul;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

#define real_t float
#include "lu.hxx"
#undef real_t


#define real_t double
#include "lu.hxx"
#undef real_t

#define real_t long double
#include "lu.hxx"
#undef real_t

#define real_t XReal<float>
#include "lu.hxx"
#undef real_t


#define real_t  XReal<double>
#include "lu.hxx"
#undef real_t

#define real_t  XReal<long double>
#include "lu.hxx"
#undef real_t

#define real_t Complex<float>
#include "lu.hxx"
#undef real_t


#define real_t  Complex<double>
#include "lu.hxx"
#undef real_t

#define real_t  Complex<long double>
#include "lu.hxx"
#undef real_t


#define real_t Complex< XReal<float> >
#include "lu.hxx"
#undef real_t


#define real_t  Complex< XReal<double> >
#include "lu.hxx"
#undef real_t

#define real_t  Complex< XReal<long double> >
#include "lu.hxx"
#undef real_t

#define real_t apq
#include "lu.hxx"
#undef real_t



    }

}
