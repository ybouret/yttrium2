#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif


#include "y/mkl/tao/3.hpp"


#include "y/mkl/tao/broker/matrix.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/system/rtti.hpp"
#include "y/system/wall-time.hpp"
#include "y/string/format.hpp"

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
        return sum <= _0;

    }

    template <typename T> static inline
    void doTest(Random::Bits      & ran,
                Tao::MatrixEngine & eng)
    {
        std::cerr << "Testing <" << System::RTTI::Name<T>() << ">" << std::endl;
        System::WallTime      chrono;
        Tao::MatrixBroker<T>  broker(eng);
        Cameo::Addition<T>  & xadd = broker.xadd();

        for(size_t nr=1;nr<=10;++nr)
        {
            std::cerr << "rows = " << std::setw(3) << nr << std::endl;
            for(size_t nc=1;nc<=10;++nc)
            {
                std::cerr << "\tcols = " << std::setw(3) << nc << ":";
                Matrix<T> a(nr,nc);
                Matrix<T> b(nr,nc);
                for(size_t k=1;k<=20;++k)
                {
                    Matrix<T> lhs(nr,k);
                    Matrix<T> rhs(k,nc);
                    FillWith<T>::Mat(ran,lhs);
                    FillWith<T>::Mat(ran,rhs);
                    uint64_t seq = 0;
                    uint64_t par = 0;
                    Y_WallTime_Update(seq, Tao::MMul(xadd,  a,lhs,rhs));
                    Y_WallTime_Update(par, Tao::MMul(broker,b,lhs,rhs));
                    if(!delta(a,b))
                    {
                        std::cerr << std::endl;
                        std::cerr << std::endl;
                        std::cerr << "a=" << a << std::endl;
                        std::cerr << "b=" << b << std::endl;
                        throw Exception("bad for nr=%u nc=%u", (unsigned)nr, (unsigned)nc);
                    }
                    //Y_ASSERT( delta(a,b) );
                    const apn    num = seq;
                    const apn    den = par;
                    const double r   = apn::Ratio<double>(num,den);
                    const String s   = Formatted::Get("%5.2lf",r);
                    std::cerr << " " << s;
                }
                std::cerr << std::endl;
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
    doTest< Complex<float> >(ran,eng);

    //doTest<apq>(ran,eng);


}
Y_UDONE()
