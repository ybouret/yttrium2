

#include "y/utest/run.hpp"
#include "y/type/ints.hpp"
#include "y/ascii/boolean.hpp"
#include <typeinfo>

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testInts()
    {
        std::cerr << "Using " << typeid(T).name() << std::endl;
        typedef IntegerFor<T> Info;
        std::cerr << "Signed: " << ASCII::Boolean::Text(Info::IsSignedType) << std::endl;
        std::cerr << "Min:    " << Info::Minimum << std::endl;
        std::cerr << "Max:    " << Info::Maximum << std::endl;


    }

}

Y_UTEST(type_ints)
{

    testInts<short>();
    testInts<unsigned short>();

    testInts<unsigned long long>();
    testInts<long long>();

}
Y_UDONE()
