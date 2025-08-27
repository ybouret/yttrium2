
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/tao/3.hpp"
#include "y/random/mt19937.hpp"

using namespace Yttrium;



Y_UTEST(algebra_ortho_space)
{
    Random::MT19937 ran;

    for(size_t cols=1;cols<=4;++cols)
    {
        std::cerr << std::endl;
        std::cerr << "cols=" << cols << std::endl;

        for(size_t rows=1;rows<=cols;++rows)
        {
            Matrix<int> P(rows,cols);
            do
            {
                for(size_t i=1;i<=rows;++i)
                    for(size_t j=1;j<=cols;++j) P[i][j] = ran.in<int>(-5,5);
            }
            while(rows!=MKL::Rank::Of(P));
            std::cerr << "P=" << P << std::endl;
            Matrix<apz> Q = MKL::OrthoSpace::Of(P);
            std::cerr << "Q=" << Q << std::endl;
        }
    }


}
Y_UDONE()


