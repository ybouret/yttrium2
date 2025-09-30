
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/apex/simplify.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "y/container/cxx/array.hpp"
#include "../main.hpp"


using namespace Yttrium;

Y_UTEST(apex_simplify)
{
    Random::MT19937 ran;

    {
        CxxArray<apn> arrn(6);
        std::cerr << Apex::Simplify::GCD(arrn) << std::endl;
        arrn[2] = 4;
        arrn[4] = 6;
        arrn[6] = 12;

        std::cerr << arrn << std::endl;
        const apn g = Apex::Simplify::GCD(arrn);

        std::cerr << "g=" << g << std::endl;

        Apex::Simplify::Array(arrn);
        std::cerr << arrn << std::endl;

        for(size_t i=arrn.size();i>0;--i)
        {
            arrn[i] *= 3;
        }

        apn denom = 9;
        std::cerr << arrn << "/" << denom << " = ";
        Apex::Simplify::Array(arrn,denom);
        std::cerr << arrn << "/" << denom << std::endl;
    }

    Matrix<apz> M(3,4);
    {
        const apz fac = 3;
        for(size_t i=1;i<=M.rows;++i)
        {
            for(size_t j=1;j<=M.cols;++j)
            {
                M[i][j] = fac * ran.in<int>(-5,5);
            }
        }
    }

    std::cerr << "M=" << M << std::endl;
    {
        const apn g = Apex::Simplify::Apply(M);
        std::cerr << "A=" << g << "*" << M << std::endl;
    }

    for(size_t i=1;i<=M.rows;++i)
    {
        for(size_t j=1;j<=M.cols;++j)
        {
            M[i][j] *= 5;
        }
    }
    apz denom = 125;
    std::cerr << M << "/" << denom << " = ";
    Apex::Simplify::Apply(M,denom);
    std::cerr << M << "/" << denom << std::endl;


}
Y_UDONE()
