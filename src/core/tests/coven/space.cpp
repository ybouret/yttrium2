
#include "y/apex/api/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "../main.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

Y_UTEST(coven_space)
{

    Random::MT19937     ran;
    Coven::IPool        ip;

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

    Coven::Survey        survey;
    Coven::QVector::Pool vp(dims);
    Coven::QFamily::Pool fp(vp);

    Coven::Tribes tribes(mu,ip,fp, &survey);

    do
    {
        tribes.generate(mu,&survey);
    } while( tribes.size > 0);






}
Y_UDONE()
