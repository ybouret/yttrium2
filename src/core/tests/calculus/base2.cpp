

#include "y/utest/run.hpp"
#include "y/calculus/base2.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace 
{
    template <typename T> static inline
    void testBase2( System::Rand &ran )
    {
        std::cerr << std::endl;
        std::cerr << "TestBase2<" << sizeof(T) << ">" << std::endl;
        Y_CHECK(!IsPowerOfTwo<T>(0));
        for(unsigned shift=0;shift<=Base2<T>::MaxShift;++shift)
        {
            const T p = Base2<T>::One << shift;
            //std::cerr << uint64_t(p) << std::endl;
            Y_ASSERT(IsPowerOfTwo(p));
            Y_ASSERT(shift==Base2<T>::ExactLog(p));
        }

        for(size_t iter=0;iter<1000;++iter)
        {
            const T x = ran.to<T>() % ( Base2<T>::MaxValue+1 );
            Y_ASSERT(x<=Base2<T>::MaxValue);
            const T n = NextPowerOfTwo(x);
            Y_ASSERT(n>=x);
            Y_ASSERT(IsPowerOfTwo(n));
        }

    }
}

Y_UTEST(calculus_base2)
{
    Y_PRINTV( uint64_t(Base2<uint8_t>::MaxValue) );
    Y_PRINTV( int64_t(Base2<int8_t>::MaxValue)   );

    Y_PRINTV(Base2<uint16_t>::MaxValue);
    Y_PRINTV(Base2<int16_t>::MaxValue);

    Y_PRINTV(Base2<uint32_t>::MaxValue);
    Y_PRINTV(Base2<int32_t>::MaxValue);

    Y_PRINTV(Base2<uint64_t>::MaxValue);
    Y_PRINTV(Base2<int64_t>::MaxValue);

    System::Rand ran;

    testBase2<uint8_t>(ran);
    testBase2<uint16_t>(ran);
    testBase2<uint32_t>(ran);
    testBase2<uint64_t>(ran);


}
Y_UDONE()
