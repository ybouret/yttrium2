
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
    void doUDT(Random::Bits &                  ran,
               const Tao::UpperDiagonalEngine &eng)
    {
        Tao::UpperDiagonalBroker<T> broker(eng);
        Cameo::Addition<T>        &xadd = broker.xadd();

        std::cerr << "broker->size = " << broker->size() << std::endl;

        for(size_t r=1;r<=3;++r)
        {
            Matrix<T> Gseq(r,r);
            Matrix<T> Gpar(r,r);
            broker.prep(Gseq);
            for(size_t c=1;c<=5;++c)
            {
                Matrix<T> A(r,c);
                FillWith<T>::Mat(ran,A);
                //std::cerr << "A=" << A << std::endl;
                Tao::Gram(xadd,Gseq,A);
                Tao::Gram(broker,Gpar,A);
                Tao::MSub(Gpar,Gseq);
                std::cerr << Gpar << std::endl;

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

