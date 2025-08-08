
#include "y/mkl/algebra/tridiag.hpp"
#include "y/mkl/complex.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"
#include "y/container/cxx/array.hpp"
#include "y/check/crc32.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T>
        class TriDiag<T> :: Code : public Object
        {
        public:
            typedef CxxArray<T>  ArrayType;
            typedef typename ScalarFor<T>::Type ScalarType;

            inline virtual ~Code() noexcept {}
            inline explicit Code(const size_t n) :
            Object(),
            size(n),
            a(n),
            b(n),
            c(n),
            gam(n),
            t0(0),
            s0(0)
            {
                assert(n>0);
            }


            inline bool solve(Writable<T> &u, const Readable<T> &r, const Readable<T> &B)
            {
                assert(size==u.size());
                assert(size==r.size());
                assert(size==B.size());

                const size_t n = size;
                if( Fabs<T>::Of(B[1]) <= s0) return false;

                T piv = B[1];
                u[1]  = r[1]/piv;
                for(size_t j=2,jm=1;j<=n;++j,++jm)
                {
                    gam[j]= c[jm]/piv;
                    piv   = B[j]-a[j]*gam[j];
                    if( Fabs<T>::Of(piv) <= s0) return false;
                    u[j]=(r[j]-a[j]*u[jm])/piv;
                }

                for(size_t j=(n-1),jp=n;j>0;--j,--jp)
                    u[j] -= gam[jp]*u[jp];

                return true;
                
            }
            


            const size_t     size;
            ArrayType        a,b,c,gam;
            const T          t0;
            const ScalarType s0;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

#define real_t float
#include "tridiag.hxx"

#undef  real_t
#define real_t double
#include "tridiag.hxx"

#undef  real_t
#define real_t long double
#include "tridiag.hxx"

#undef  real_t
#define real_t XReal<float>
#include "tridiag.hxx"

#undef  real_t
#define real_t XReal<double>
#include "tridiag.hxx"

#undef  real_t
#define real_t XReal<long double>
#include "tridiag.hxx"


#undef  real_t
#define real_t Complex<float>
#include "tridiag.hxx"

#undef  real_t
#define real_t Complex<double>
#include "tridiag.hxx"

#undef  real_t
#define real_t Complex<long double>
#include "tridiag.hxx"

#undef  real_t
#define real_t Complex< XReal<float> >
#include "tridiag.hxx"

#undef  real_t
#define real_t Complex< XReal<double> >
#include "tridiag.hxx"

#undef  real_t
#define real_t Complex< XReal<long double> >
#include "tridiag.hxx"


#undef  real_t
#define real_t apq
#include "tridiag.hxx"




    }

}

