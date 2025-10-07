

#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/ode/explicit/integrator.hpp"
#include "y/mkl/ode/explicit/cash-karp.hpp"
#include "y/mkl/ode/explicit/dormand-prince.hpp"
#include "y/mkl/ode/example.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/xreal.hpp"
#include "y/string.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "../../core/tests/main.hpp"
#include "y/random/in2d.hpp"

using namespace Yttrium;
using namespace MKL;


template <typename T> static inline
void saveTo(OutputStream &fp, const T x, const Readable<T> &y)
{
    fp("%.15g", double(x) );
    for(size_t i=1;i<=y.size();++i) fp(" %.15g", double(y[i]));
    fp << "\n";
}


template <typename T, template <typename> class Step>
static inline void TestExample(const char * const id, Random::Bits &ran)
{
    static const unsigned      np = 100;
    Step<T>                    step;
    ODE::ExplicitIntegrator<T> odeint;
    const String               uid = String(step.callSign()) + '-' + String(id);

    T              x     = 0;
    const T        x_end = 7;
    const T        dx    = (x_end-x) / (T) np;
    const T        dx1   = dx / (T) 10.0;;
    {
        std::cerr << "Exponential/" << uid << std::endl;
        const String fileName = "q-exponential-" + uid + ".dat";
        OutputFile   fp(fileName);
        CxxArray<T> y(1),dydx(1);

        ODE::dExponential<T> dExp(-0.7f);


        y[1] = 1;
        saveTo(fp,x,y);
        for(unsigned i=1;i<=np;++i)
        {
            const T x1 = x;
            const T x2 = x = (((T) (i) ) * x_end) / (T) np;
            odeint(y,x1,x2,dx1,dExp,0,step);
            saveTo(fp,x,y);
        }

    }

    {
        std::cerr << "Spring/" << uid << std::endl;
        const String fileName = "q-spring-" + uid + ".dat";
        OutputFile   fp(fileName);
        CxxArray<T>  y(2),dydx(2);

        ODE::dSpring<T> spring(0.7f,0.01f);
        x    = 0;
        y[1] = 1;
        y[2] = 0;
        saveTo(fp,x,y);
        for(unsigned i=1;i<=np;++i)
        {
            const T x1 = x;
            const T x2 = x = (((T) (i) ) * x_end) / (T) np;
            odeint(y,x1,x2,dx1,spring,0,step);
            saveTo(fp,x,y);
        }
    }



    {
        std::cerr << "Astra/" << uid << std::endl;
        const V2D<T>   r0    =  ( (T)0.5 +ran.to<T>()) * Random::OnCircle< V2D<T> >(ran);
        const T        omega = (T)1.0 + ran.to<T>();
        ODE::dAstra<T> astra(r0,omega);
        {
            const String fileName = "q-astra0-" + uid + ".dat";
            OutputFile   fp(fileName);
            CxxArray<T>  y(4),dydx(4);
            x    = 0;
            astra.init(y);
            saveTo(fp,x,y);
            for(unsigned i=1;i<=np;++i)
            {
                const T x1 = x;
                const T x2 = x = (((T) (i) ) * x_end) / (T) np;
                odeint(y,x1,x2,dx1,astra,0,step);
                saveTo(fp,x,y);
            }
        }

        {
            const String fileName = "q-astra1-" + uid + ".dat";
            OutputFile   fp(fileName);
            CxxArray<T>  y(4),dydx(4);
            x    = 0;
            astra.init(y);
            saveTo(fp,x,y);
            for(unsigned i=1;i<=np;++i)
            {
                const T x1 = x;
                const T x2 = x = (((T) (i) ) * x_end) / (T) np;
                odeint(y,x1,x2,dx1,astra,&astra.proj,step);
                saveTo(fp,x,y);
            }
        }

    }
    


}

Y_UTEST(ode_expl)
{
    Random::MT19937 ran;
    TestExample<float,          ODE::CashKarp>("f",ran);
    TestExample<XReal<double> , ODE::CashKarp>("xd",ran);
    TestExample<float,          ODE::DormandPrince>("f",ran);
    TestExample<XReal<double> , ODE::DormandPrince>("xd",ran);
}
Y_UDONE()

