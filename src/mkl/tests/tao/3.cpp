#include "y/mkl/tao/3.hpp"


#include "y/mkl/tao/broker/matrix.hpp"
#include "y/utest/run.hpp"
//#include "y/random/mt19937.hpp"
#include "../../../core/tests/main.hpp"
//#include "y/container/sequence/vector.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"

using namespace Yttrium;
using namespace MKL;

namespace   {

    template <typename T> static inline
    void doTest(Random::Bits      & ran,
                Tao::MatrixEngine & eng)
    {

        Tao::MatrixBroker<T>  broker(eng);
        Cameo::Addition<T>  & xadd = broker.xadd();
        for(size_t nr=1;nr<=3;++nr)
        {
            for(size_t nc=1;nc<=3;++nc)
            {
                Matrix<T> a(nr,nc);
                for(size_t k=1;k<=4;++k)
                {
                    Matrix<T> lhs(nr,k);
                    Matrix<T> rhs(k,nc);
                    FillWith<T>::Mat(ran,lhs);
                    FillWith<T>::Mat(ran,rhs);
                    Tao::MMul(xadd,a,lhs,rhs);
                    Tao::MMul(broker,a,lhs,rhs);

                }
            }
        }

    }

}

Y_UTEST(tao_3)
{
    Random::MT19937       ran;
    Concurrent::Processor cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::MatrixEngine     eng = new Tao::MatrixSpawn( cpu );

    doTest<float>(ran,eng);


}
Y_UDONE()
