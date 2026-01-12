
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/broker/upper-diagonal.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"


using namespace Yttrium;
using namespace MKL;


namespace
{
    template <typename T> static inline
    void doUDT(Random::Bits &                  ran,
               const Tao::UpperDiagonalEngine &eng)
    {
        Tao::UpperDiagonalBroker<T> broker(eng);

        std::cerr << "broker->size = " << broker->size() << std::endl;

        for(size_t r=1;r<=3;++r)
        {
            Matrix<T> G(r,r);
            broker.prep(G);
            for(size_t c=1;c<=5;++c)
            {
                Matrix<T> A(r,c);
                FillWith<T>::Mat(ran,A);
                std::cerr << "A=" << A << std::endl;
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

