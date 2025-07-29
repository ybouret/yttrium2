
#include "y/apex/api/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "../main.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

namespace
{
    static inline void Run(const Matrix<int> &    mu,
                           Coven::QVector::Pool & vp,
                           const unsigned         strategy,
                           Coven::Survey &        survey)
    {

        Coven::IPool         ip;
        Coven::QFamily::Pool fp(vp);

        Coven::Tribes tribes(mu,ip,fp, &survey);
        do
        {
            tribes.generate(mu,&survey,strategy);
        } while( tribes.size > 0);

        std::cerr << "found=" << survey->size << " / " << survey.calls << std::endl;
    }
}

Y_UTEST(coven_space)
{

    Random::MT19937     ran;

    size_t     dims  = 4;
    size_t     rows  = 4;
    int        ampli = 5;
    if(argc>1) dims  = ASCII::Convert::To<size_t>(argv[1],"dims");
    if(argc>2) rows  = ASCII::Convert::To<size_t>(argv[2],"rows");
    if(argc>3) ampli = ASCII::Convert::To<int>   (argv[3],"ampli");

    Matrix<int> mu(rows,dims);

    for(size_t i=1;i<=rows;++i)
    {
        for(size_t j=1;j<=dims;++j)
        {
            mu[i][j] = ran.in<int>(-ampli,ampli);
        }
    }

    Coven::QVector::Pool vp(mu.cols);

    Coven::Survey survey0(vp);
    Run(mu,vp,0,survey0);

    Coven::Survey survey1(vp);
    Run(mu,vp,Coven::Tribes::DitchReplicae,survey1);

    Coven::Survey survey2(vp);
    Run(mu,vp,Coven::Tribes::GroupFamilies,survey2);

    std::cerr << "survey0 : " << survey0->size << " / " << survey0.calls << std::endl;
    std::cerr << "survey1 : " << survey1->size << " / " << survey1.calls << std::endl;
    std::cerr << "survey2 : " << survey2->size << " / " << survey2.calls << std::endl;



}
Y_UDONE()
