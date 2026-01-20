
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/3.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/system/wall-time.hpp"
#include "y/apex/rational.hpp"
#include "y/string/format.hpp"

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
        System::WallTime           chrono;

        for(size_t r=1;r<=20;++r)
        {
            (std::cerr << "rows=" << std::setw(3) << r << " [").flush();
            Matrix<T> Gseq(r,r);
            Matrix<T> Gpar(r,r);
            broker.prep(Gseq);
            for(size_t c=1;c<=20;++c)
            {
                Matrix<T> A(r,c);
                uint64_t tseq=0, tpar=0;
                const uint64_t loop = System::WallTime::Ticks();
                do
                {
                    FillWith<T>::Mat(ran,A);
                    Y_WallTime_Update(tseq, Tao::Gram(xadd,Gseq,A)   );
                    Y_WallTime_Update(tpar, Tao::Gram(broker,Gpar,A) );
                } while( chrono(System::WallTime::Ticks()-loop) <= 0.01L );

                const apn    numer = tseq;
                const apn    denom = tpar;
                const float ratio  = apn::Ratio<float>(numer,denom);
                const String s     = Formatted::Get("%5.2f",ratio);
                std::cerr << " " << s;

                Y_ASSERT( delta(Gseq,Gpar) );
            }
            std::cerr << "]" << std::endl;
        }


    }
}

Y_UTEST(tao_d)
{

    Random::MT19937          ran;
    Concurrent::Processor    cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::UpperDiagonalEngine eng = new Tao::UpperDiagonalSpawn( cpu );


    doUDT<float>(ran,eng);
    doUDT<double>(ran,eng);


}
Y_UDONE()

