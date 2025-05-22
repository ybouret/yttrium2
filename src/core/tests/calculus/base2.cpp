

#include "y/utest/run.hpp"
#include "y/calculus/base2.hpp"

using namespace Yttrium;

namespace 
{
    template <typename T> static inline
    void testBase2()
    {
        std::cerr << std::endl;
        std::cerr << "TestBase2<" << sizeof(T) << ">" << std::endl;
        Y_CHECK(!IsPowerOfTwo<T>(0));
        for(unsigned shift=0;shift<=Base2<T>::MaxShift;++shift)
        {
            const T p = Base2<T>::One << shift;
            std::cerr << uint64_t(p) << std::endl;
            Y_ASSERT(IsPowerOfTwo(p));
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

    testBase2<uint8_t>();
    testBase2<uint16_t>();
    testBase2<uint32_t>();
    testBase2<uint64_t>();


}
Y_UDONE()
