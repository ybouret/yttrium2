#include "y/utest/run.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/rational.hpp"
#include "y/container/cxx/array.hpp"

using namespace Yttrium;

namespace
{
    typedef apq (*GetWeightSquare)(const unit_t x, const unit_t y);

    static inline
    void computeDiff(const unit_t delta, GetWeightSquare weight)
    {
        Y_ASSERT(delta>=1);
        Y_ASSERT(0!=weight);
        const size_t side = 1+2*delta;
        const size_t N    = side*side;
        std::cerr << "N=" << N << std::endl;

        Matrix<apq>   mu(6,6);
        Matrix<apq>   cf(6,N);
        CxxArray<apq> tmp(6);

        size_t k = 0;
        for(unit_t y=-delta;y<=delta;++y)
        {
            for(unit_t x=-delta;x<=delta;++x)
            {
                ++k;
                const apq w2 = weight(x,y);
                std::cerr << w2 << std::endl;
                const apq w2x  = w2  * x;
                const apq w2y  = w2  * y;
                const apq w2xx = w2x * x;
                const apq w2xy = w2x * y;
                const apq w2yy = w2y * y;
                cf[1][k] = w2;
                cf[2][k] = w2x;
                cf[3][k] = w2y;
                cf[4][k] = w2xx;
                cf[5][k] = w2xy;
                cf[6][k] = w2yy;

                for(size_t i=1;i<=6;++i)
                {
                    const apq f  = cf[i][k];
                    const apq fx = f*x;
                    const apq fy = f*y;
                    mu[1][i] += f;
                    mu[2][i] += fx;
                    mu[3][i] += fy;
                    mu[4][i] += fx*x;
                    mu[5][i] += fx*y;
                    mu[6][i] += fy*y;
                }

            }
        }
        Y_ASSERT(N==k);

        std::cerr << "mu=" << mu << std::endl;
        std::cerr << "cf=" << cf << std::endl;

        MKL::LU<apq> lu(6);
        if(!lu.build(mu)) throw Exception("bad mu matrix");
        lu.solve(mu,cf,tmp);
        std::cerr << "res=" << cf << std::endl;

        

    }

    static inline apq GetOne(const unit_t, const unit_t) { return 1; }
    static inline apq GetOneOverR2(const unit_t x, const unit_t y)
    {
        apq res = 1;
        return res / (x*x+y*y);
    }

}

Y_UTEST(diff)
{
    std::cerr << "Computing Differential Filters" << std::endl;

    computeDiff(1,GetOne);

}
Y_UDONE()
