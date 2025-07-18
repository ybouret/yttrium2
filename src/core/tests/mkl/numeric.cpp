#include "y/mkl/numeric.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{

    static int w = 32;

#define FIELD(NAME) std::cerr << std::setw(w) << #NAME << " = " << Numeric<T>::NAME << std::endl

    template <typename T> static inline
    void DisplayNumeric(const char * const typeName)
    {
        std::cerr << std::endl;
        std::cerr << "---- " << typeName << " ----" << std::endl;
        FIELD(RADIX);
        FIELD(PI);
        FIELD(EPSILON);
        FIELD(MAX);
        FIELD(MIN);
        FIELD(MANT_DIG);
        FIELD(DIG);
        FIELD(MIN_EXP);
        FIELD(MAX_EXP);
        FIELD(MAX_10_EXP);
        FIELD(MIN_10_EXP);
        FIELD(FTOL);
        FIELD(SQRT_EPSILON);
        FIELD(GOLDEN);
        FIELD(INV_GOLDEN);
    }

    template <typename T> static inline
    void DisplayTheta(const char * const typeName)
    {
        const T Theta = Numeric<T>::MIN / Numeric<T>::EPSILON;
        std::cerr << std::setw(16) << typeName << " ThetaMin =" << Theta << std::endl;

    }

#define SHOW_THETA(TYPE) DisplayTheta<TYPE>( #TYPE )
}

#define SHOW(TYPE) DisplayNumeric<TYPE>( #TYPE )

Y_UTEST(mkl_numeric)
{

    SHOW(float);
    SHOW(double);
    SHOW(long double);

    SHOW(XReal<float>);
    SHOW(XReal<double>);
    SHOW(XReal<long double>);

    std::cerr << std::endl;
    SHOW_THETA(float);
    SHOW_THETA(double);
    SHOW_THETA(long double);



}
Y_UDONE()
