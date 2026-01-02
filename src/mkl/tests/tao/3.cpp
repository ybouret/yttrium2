#include "y/mkl/tao/3.hpp"


#include "y/mkl/tao/broker/matrix.hpp"
#include "y/utest/run.hpp"
//#include "y/random/mt19937.hpp"
#include "../../../core/tests/main.hpp"
//#include "y/container/sequence/vector.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/system/rtti.hpp"

using namespace Yttrium;
using namespace MKL;

namespace   {

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
        //std::cerr << "|delta|=" << sum << std::endl;
        return sum <= _0;

    }

    template <typename T> static inline
    void doTest(Random::Bits      & ran,
                Tao::MatrixEngine & eng)
    {
        std::cerr << "Testing <" << System::RTTI::Name<T>() << ">" << std::endl;
        Tao::MatrixBroker<T>  broker(eng);
        Cameo::Addition<T>  & xadd = broker.xadd();
        for(size_t nr=1;nr<=3;++nr)
        {
            for(size_t nc=1;nc<=3;++nc)
            {
                Matrix<T> a(nr,nc);
                Matrix<T> b(nr,nc);
                for(size_t k=1;k<=4;++k)
                {
                    Matrix<T> lhs(nr,k);
                    Matrix<T> rhs(k,nc);
                    FillWith<T>::Mat(ran,lhs);
                    FillWith<T>::Mat(ran,rhs);
                    Tao::MMul(xadd,  a,lhs,rhs);
                    Tao::MMul(broker,b,lhs,rhs);
                    //std::cerr << a << "/" << b << std::endl;
                    Y_ASSERT( delta(a,b) );
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
    doTest<double>(ran,eng);


}
Y_UDONE()
