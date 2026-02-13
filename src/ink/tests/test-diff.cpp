#include "y/utest/run.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/apex/rational.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/ratsimp.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/gaussian.hpp"
#include "y/cameo/addition.hpp"

#include "y/ink/image/formats.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/unique.hpp"
#include "y/ink/ops/ld.hpp"
#include "y/color/x11.hpp"
#include "y/string/format.hpp"
#include "y/ink/draw/line.hpp"

using namespace Yttrium;

namespace
{
    typedef apq (*GetWeightSquare)(const unit_t x, const unit_t y);

    static const char * const Name[8] = { 0, "a" , "b", "c" , "d", "e", "f", 0};

    static inline
    void computeDiff(const unit_t delta, GetWeightSquare weightSqr)
    {
        Y_ASSERT(delta>=1);
        Y_ASSERT(0!=weightSqr);
        const size_t side = 1+2*delta;
        const size_t N    = side*side;
        std::cerr << "delta = " << delta << std::endl;
        std::cerr << "N     = " << N << std::endl;

        Matrix<apq>   mu(6,6);
        Matrix<apq>   cf(6,N);
        CxxArray<apq> tmp(6);
        CxxArray<apz> zf(6);

        size_t k = 0;
        for(unit_t y=-delta;y<=delta;++y)
        {
            for(unit_t x=-delta;x<=delta;++x)
            {
                ++k;
                const apq w2   = weightSqr(x,y);
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

        //std::cerr << "mu=" << mu << std::endl;
        //std::cerr << "cf=" << cf << std::endl;

        MKL::LU<apq> lu(6);
        if(!lu.build(mu)) throw Exception("bad mu matrix");
        lu.solve(mu,cf,tmp);
        Matrix<apq>
        a(side,side),
        b(side,side),
        c(side,side),
        d(side,side),
        e(side,side),
        f(side,side);
        Matrix<apq> * const mm[8] = { 0, &a, &b, &c, &d, &e, &f, 0 };




        for(size_t i=1;i<=6;++i)
        {
            (void) Apex::RatSimp::Array(cf[i]);

            // std::cerr << "\t" << Name[i] << " = " << cf[i] << std::endl; // " / " << tmp[i] << std::endl;
            Matrix<apq> &m = *mm[i];
            for(size_t k=1;k<=N;++k)
            {
                *(m()+(k-1)) = cf[i][k];
            }
            std::cerr << "\t" << Name[i] << " = " << m << std::endl; // " / " << tmp[i] << std::endl;
        }





    }

    static inline apq GetOne(const unit_t, const unit_t) { return 1; }
    static inline apq GetOneOverR2(const unit_t x, const unit_t y)
    {
        apq res = 1;
        if(x||y)
            return res / (x*x+y*y);
        return res;
    }

}

using namespace Ink;

#include "y/concurrent/api/simd/crew.hpp"

namespace
{
    static inline void putWhite(const unit_t x, const unit_t y, Image &img)
    {
        img[y][x] = Y_White;
    }
}

Y_UTEST(diff)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           par(cpus);

    std::cerr << "Computing Differential Filters" << std::endl;

    computeDiff(1,GetOne);
    computeDiff(1,GetOneOverR2);
    computeDiff(2,GetOne);

    {
        const Formats & IMG = Formats::Std();
        const unit_t    delta = 1;
        const size_t    side  = delta*2 + 1;
        Image           img(side,side);
        Point           center(delta,delta);
        Vector<Point>   border;

        for(unit_t i=img.lower.x;i<=img.upper.x;++i)
        {
            border << Point(i,img.lower.y);
            border << Point(i,img.upper.y);
        }

        for(unit_t j=img.lower.y;j<=img.upper.y;++j)
        {
            border << Point(img.lower.x,j);
            border << Point(img.upper.x,j);
        }
        std::cerr << "#border=" << border.size() << std::endl;
        const size_t nb = Algo::Unique(border).size();
        std::cerr << "#border=" << border.size() << std::endl;
        std::cerr << "border=" << border << std::endl;

        unsigned count=0;
        for(size_t i=1;i<=nb;++i)
        {
            const Point ini = border[i];
            for(size_t j=1;j<i;++j)
            {
                const Point end = border[j];
                Y_ASSERT(ini!=end);

                LoadPixel::Set(par,img,Y_Black);
                Draw::Line_(ini.x, ini.y, end.x, end.y, putWhite, img);

                ++count;
                const String fileName = Formatted::Get("diff%u.png",count);
                IMG.save(img,fileName, 0);

            }
        }



    }


}
Y_UDONE()
