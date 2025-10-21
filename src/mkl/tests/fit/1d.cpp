#include "y/mkl/fit/samples.hpp"
#include "y/mkl/fit/raw-sample.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/string/env.hpp"
#include "y/string/boolean.hpp"

#include "y/mkl/fit/optimizer.hpp"

using namespace Yttrium;
using namespace MKL;

static const double _t1[]    = { 30,80,140,200,270,320,430,550,640,720,830,890 };
static const double _x1[]    = { 4.414520,5.011710,5.632319,6.194379,6.721311,7.330211,8.009368,8.735363,9.297424,9.707260,10.339578,10.878220};
static const size_t _n1      = sizeof(_t1)/sizeof(_t1[0]);

static const double _t2[]    = { 60,120,200,270,360,460,580,670,790,920,1040 };
static const double _x2[]    = { 5.199063,5.854801,6.662763,7.365340,8.067916,8.782201,9.578454,10.175644,10.878220,11.651054,12.213115};
static const size_t _n2      = sizeof(_t2)/sizeof(_t2[0]);

template <typename T>
T getF(const T t, const Fit::Variables &vars, const Readable<T> &aorg)
{
    const T zero(0);
    const T &t0 = vars["t0"][aorg];
    const T &D  = vars["D"][aorg];

    if(t<=t0) return zero;
    const T arg = D * (t-t0);

    return Sqrt<T>::Of(arg);
}

template <typename T>
T getG(Writable<T> &dFda,
       const T               t,
       const Fit::Variables &vars,
       const Readable<T   > &aorg,
       const Readable<bool> & )
{
    const T zero(0);
    const Fit::Variable &_t0 = vars["t0"];
    const Fit::Variable &_D  = vars["D"];

    const T &t0 = _t0[aorg];
    const T &D  = _D[aorg];
    T & dF_dt0  = dFda[_t0.indx];
    T & dF_dD   = dFda[_D.indx];

    dF_dt0 = zero;
    dF_dD  = zero;

    if(t<=t0) return zero;
    const T dt  = t-t0;
    const T arg = D * dt;
    const T res = Sqrt<T>::Of(arg);
    const T den = res+res;

    dF_dD  =  dt/den;
    dF_dt0 = - D/den;

    return res;
}



#include "y/system/rtti.hpp"
#define t0_ini -100
#define D1_ini 0.15f
#define D2_ini 0.20f

template <typename T> static inline
void testFit(const Fit::Parameters &params)
{
    typedef typename FCPU<T>::Type fcpu_t;
    std::cerr << std::endl;
    std::cerr << "Testing Fit / " << System::RTTI::Name<T>() << std::endl;

    const T      zero(0);
    Vector<T>    aorg(params->size(),zero);
    Vector<bool> used(params->size(),true);
    Vector<T>    aerr(params->size(),zero);

    T & t0 = (aorg[ params["t0"].indx ]);
    T & D1 = (aorg[ params["D1"].indx ]);
    T & D2 = (aorg[ params["D2"].indx ]);

    t0 = t0_ini;
    D1 = D1_ini;
    D2 = D2_ini;


    std::cerr << "t0=" << t0 << std::endl;
    std::cerr << "D1=" << D1 << std::endl;
    std::cerr << "D2=" << D2 << std::endl;

    params.queryEnv(used);

    Vector<T> t1, x1, x1f;
    for(size_t i=0;i<_n1;++i)
    {
        t1 << (fcpu_t)_t1[i];
        x1 << (fcpu_t)_x1[i];
        x1f << zero;
    }

    Vector<T> t2, x2, x2f;
    for(size_t i=0;i<_n2;++i)
    {
        t2 << (fcpu_t)_t2[i];
        x2 << (fcpu_t)_x2[i];
        x2f << zero;
    }

    Fit::Samples<T,T> samples("Sall");

    Fit::Sample<T,T> & S1 = samples( new Fit::Sample<T,T>("S1",t1,x1,x1f) );
    Fit::Sample<T,T> & S2 = samples( new Fit::Sample<T,T>("S2",t2,x2,x2f) );

    S1.vars << params["t0"] << Fit::Alias("D", params["D1"]);
    std::cerr << "#S1    = " << S1.count() << std::endl;
    std::cerr << "|_vars = " << S1.vars << std::endl;
    std::cerr << std::endl;

    S2.vars << params["t0"] << Fit::Alias("D", params["D2"]);
    std::cerr << "#S2    = " << S2.count() << std::endl;
    std::cerr << "|_vars = " << S2.vars << std::endl;
    std::cerr << std::endl;

    S1.save("S1.dat");
    S2.save("S2.dat");

    const T D2_1 = S1.computeD2_(getF<T>,aorg);
    std::cerr << "D2_1  = " << (double)D2_1 << std::endl;
    const T D2_2 = S2.computeD2_(getF<T>,aorg);
    std::cerr << "D2_2  = " << (double)D2_2 << std::endl;

    const T D2_A = samples.computeD2_(getF<T>,aorg);
    std::cerr << "D2_A  = " << (double)D2_A << std::endl;
    std::cerr << std::endl;

    const T D2_1b = S1.computeD2full_(getG<T>,aorg,used);
    std::cerr << "D2_1b = " << (double)D2_1b << std::endl;
    std::cerr << "beta  = " << S1.beta  << std::endl;
    std::cerr << "alpha = " << S1.alpha << std::endl;
    std::cerr << std::endl;


    const T D2_2b = S2.computeD2full_(getG<T>,aorg,used);
    std::cerr << "D2_2b = " << (double)D2_2b << std::endl;
    std::cerr << "beta  = " << S2.beta << std::endl;
    std::cerr << "alpha = " << S2.alpha << std::endl;
    std::cerr << std::endl;


    const T D2_Ab = samples.computeD2full_(getG<T>,aorg,used);
    std::cerr << "D2_Ab = " << (double)D2_Ab << std::endl;
    std::cerr << "beta  = " << samples.beta << std::endl;
    std::cerr << "alpha = " << samples.alpha << std::endl;
    std::cerr << std::endl;


    Fit::Optimizer<T> fit;
    bool              verbose = true;
    XMLog xml(std::cerr,verbose);

    std::cerr << std::endl;
    fit.run_(xml,S1,getF<T>,getG<T>,aorg,used,aerr);
    S1.save(S1.name + ".dat");

    //return;

    std::cerr << std::endl;
    t0 = t0_ini;
    D1 = D1_ini;
    D2 = D2_ini;
    fit.run_(xml,S2,getF<T>,getG<T>,aorg,used,aerr);
    S2.save(S2.name + ".dat");

    return;


    std::cerr << std::endl;
    t0 = t0_ini;
    D1 = D1_ini;
    D2 = D2_ini;
    fit.run_(xml,samples,getF<T>,getG<T>,aorg,used,aerr);

    S1.save(S1.name + "-all.dat");
    S2.save(S2.name + "-all.dat");


}



Y_UTEST(fit_1d)
{
    // declare parameters
    Fit::Parameters params;
    params << "t0" << "D1" << "D2";
    std::cerr << "params=" << params << std::endl;

    Fit::Samples<double,double> samples("Sall");

    Vector<double> x1f(_n1,0);
    Vector<double> x2f(_n2,0);

    Fit::Sample<double,double> &S1 = samples( new Fit::RawSample<double,double>("S1",_t1,_x1,_n1,x1f) );
    Fit::Sample<double,double> &S2 = samples( new Fit::RawSample<double,double>("S2",_t2,_x2,_n2,x2f) );

    S1.vars << params["t0"] << Fit::Alias("D", params["D1"]);
    S2.vars << params["t0"] << Fit::Alias("D", params["D2"]);


    std::cerr << "#S1    = " << S1.count() << std::endl;
    std::cerr << "|_vars = " << S1.vars << std::endl;

    std::cerr << "#S2    = " << S2.count() << std::endl;
    std::cerr << "|_vars = " << S2.vars << std::endl;


    testFit< XReal<float> >(params);
    testFit<float>(params);
    testFit<double>(params);


    if(false)
        for(size_t nvar=1;nvar<=10;++nvar)
        {
            const size_t twice = nvar * (nvar+3);
            Y_ASSERT( 0 == (twice&1) );
            std::cerr << "nvar=" << nvar << " => " << (twice>>1) << std::endl;
        }

}
Y_UDONE()

