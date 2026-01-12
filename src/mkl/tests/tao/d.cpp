
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/3.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"


using namespace Yttrium;
using namespace MKL;


namespace
{

    template <typename T> static inline
    bool delta(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        typedef Fabs<T> FabsType;
        typedef typename FabsType::ScalarType S;
        Cameo::Addition<S> sadd;

        sadd.ldz();

        {
            const T * p = lhs();
            const T * q = rhs();
            for(size_t i=lhs.items;i>0;--i)
            {
                const T d = *(p++) - *(q++);
                sadd << FabsType::Of(d);
            }
        }

        const S sum = sadd.sum();
        const S _0  = 0;
        return sum <= _0;

    }

    template <typename T> static inline
    void doUDT(Random::Bits &                  ran,
               const Tao::UpperDiagonalEngine &eng)
    {
        Tao::UpperDiagonalBroker<T> broker(eng);
        Cameo::Addition<T>        &xadd = broker.xadd();


        for(size_t r=1;r<=10;++r)
        {
            std::cerr << "rows=" << r << std::endl;
            Matrix<T> Gseq(r,r);
            Matrix<T> Gpar(r,r);
            broker.prep(Gseq);
            for(size_t c=1;c<=10;++c)
            {
                Matrix<T> A(r,c);
                FillWith<T>::Mat(ran,A);
                //std::cerr << "A=" << A << std::endl;
                Tao::Gram(xadd,Gseq,A);
                Tao::Gram(broker,Gpar,A);
                Y_ASSERT( delta(Gseq,Gpar) );
            }
        }


    }
}

Y_UTEST(tao_d)
{

    Random::MT19937          ran;
    Concurrent::Processor    cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::UpperDiagonalEngine eng = new Tao::UpperDiagonalSpawn( cpu );


    doUDT<float>(ran,eng);


}
Y_UDONE()

