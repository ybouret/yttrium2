
#include "y/mkl/tao/3.hpp"

#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"

#include "y/container/cxx/array.hpp"


using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testLU(Random::Bits &ran)
    {

        MKL::LU<T> lu;
        Cameo::Addition<T> xadd;
        for(size_t n=1;n<=3;++n)
        {
            while(true)
            {
                Matrix<T> a(n,n);
                FillWith<T>::Mat(ran,a);
                const Matrix<T> a0(a);
                if(!lu.build(a)) continue;
                std::cerr << "a=" << a0 << std::endl;

                //const T d = lu.det(a);
                //std::cerr << "d=" << d << std::endl;

                const CxxArray<T> b(n);
                FillWith<T>::Seq(ran,Coerce(b));
                //std::cerr << "b=" << b << std::endl;

                CxxArray<T> u(b);
                lu.solve(a,u);
                //std::cerr << "u=" << u << std::endl;

                CxxArray<T> au(n);
                MKL::Tao::Mul(xadd,au,a0,u);

                //std::cerr << "au=" << au << std::endl;
                for(size_t i=n;i>0;--i) au[i] -= b[i];
                //const T residue = MKL::Tao::Norm2(xadd,au);
                //std::cerr << "residue=" << residue << std::endl;

                Matrix<T> ia(n,n);
                lu.inv(a,ia);
                //std::cerr << "ia=" << ia << std::endl;
                Matrix<T> I(n,n);
                MKL::Tao::MMul(xadd,I,a0,ia);
                std::cerr << "I=" << I << std::endl;

#if 0
                xadd.ldz();
                for(size_t i=n;i>0;--i)
                {
                    for(size_t j=n;j>0;--j)
                    {
                        if(i==j)
                        {
                            const T delta = I[i][i] - T(1);
                            xadd.addSquared(delta);
                        }
                        else
                        {
                            xadd.addSquared(I[i][j]);
                        }

                    }
                }
                const T residueInv = xadd.sum();
                std::cerr << "residueInv=" << residueInv << std::endl;
#endif

                break;
            }
        }

    }
}

Y_UTEST(algebra_lu)
{
    Random::MT19937 ran;
    testLU<float>(ran);

    //testLU< Complex<double> >(ran);

    testLU<apq>(ran);

}
Y_UDONE()
