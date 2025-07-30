
#include "y/apex/api/coven/tribes.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "../main.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;

namespace
{
    static bool Verbose = true;

    static inline size_t Run(const Matrix<int> &    mu,
                             Coven::QVector::Pool & vp,
                             const bool             optimize,
                             Coven::Survey &        survey)
    {

        std::cerr << std::endl;
        std::cerr << "-- Running Coven Space -- " << std::endl;
        Coven::IPool         ip;
        Coven::QFamily::Pool fp(vp);
        XMLog                xml(std::cerr,Verbose);
        Coven::Tribes tribes(xml,mu,ip,fp, &survey);
        size_t count = tribes.size;
        do
        {
            count += tribes.generate(xml,mu,&survey,optimize);
        } while( tribes.size > 0);

        //std::cerr << "found=" << survey->size << " / " << survey.calls << std::endl;
        return count;
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
    const size_t  gen0 = Run(mu,vp,false,survey0);

    Coven::Survey survey1(vp);
    const size_t  gen1 = Run(mu,vp,true,survey1);

    std::cerr << "survey0 : " << survey0->size << " / " << survey0.calls << " / gen=" << gen0 << std::endl;
    std::cerr << "survey1 : " << survey1->size << " / " << survey1.calls << " / gen=" << gen1 << std::endl;

    Y_ASSERT(survey1==survey0);

#if 0
    Coven::Survey survey0(vp);
    const size_t  gen0 = Run(mu,vp,0,survey0);

    Coven::Survey survey1(vp);
    const size_t gen1  = Run(mu,vp,Coven::Tribes::EndEarlyBasis,survey1);

    Y_ASSERT(survey1==survey0);

    Coven::Survey survey2(vp);
    const size_t gen2 = Run(mu,vp,Coven::Tribes::UseHyperPlane,survey2);
    Y_ASSERT(survey2==survey0);


    Coven::Survey survey3(vp);
    const size_t  gen3 = Run(mu,vp,Coven::Tribes::DitchReplicae,survey3);
    Y_ASSERT(survey3==survey0);

    Coven::Survey survey4(vp);
    const size_t gen4 = Run(mu,vp,Coven::Tribes::GroupFamilies,survey4);



    std::cerr << "survey0 : " << survey0->size << " / " << survey0.calls << " / gen=" << gen0 << std::endl;
    std::cerr << "survey1 : " << survey1->size << " / " << survey1.calls << " / gen=" << gen1 << std::endl;
    std::cerr << "survey2 : " << survey2->size << " / " << survey2.calls << " / gen=" << gen2 << std::endl;
    std::cerr << "survey3 : " << survey3->size << " / " << survey3.calls << " / gen=" << gen3 << std::endl;
    std::cerr << "survey4 : " << survey4->size << " / " << survey4.calls << " / gen=" << gen4 << std::endl;
#endif



}
Y_UDONE()
