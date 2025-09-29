
#include "y/mkl/ode/explicit/integrator.hpp"
#include "y/mkl/ode/explicit/cash-karp.hpp"
#include "y/mkl/ode/example.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/xreal.hpp"
#include "y/string.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace MKL;


template <typename T> static inline
void saveTo(OutputStream &fp, const T x, const Readable<T> &y)
{
    fp("%.15g", double(x) );
    for(size_t i=1;i<=y.size();++i) fp(" %.15g", double(y[i]));
    fp << "\n";
}

template <typename T>
static inline void TestExample(const char * const id)
{
    ODE::CashKarp<T>           step;
    ODE::ExplicitIntegrator<T> odeint;
    
    T            x     = 0;
    const T      x_end = 7;
    const size_t np    = 100;
    const T      dx    = (x_end-x) / (T) np;
    const T      dx1   = dx / (T) 10.0;;
    {
        std::cerr << "Exponential/" << id << std::endl;
        const String fileName = "q-exponential-" + String(id) + ".dat";
        OutputFile   fp(fileName);
        CxxArray<T> y(1),dydx(1);

        ODE::dExponential<T> dExp(-0.7);


        y[1] = 1;
        saveTo(fp,x,y);
        for(size_t i=1;i<=np;++i)
        {
            const T x1 = x;
            const T x2 = x = (((T) (i) ) * x_end) / (T) np;
            odeint(y,x1,x2,dx1,dExp,0,step);
            saveTo(fp,x,y);
        }

    }

    {
        std::cerr << "Spring/" << id << std::endl;
        const String fileName = "q-spring-" + String(id) + ".dat";
        OutputFile   fp(fileName);
        CxxArray<T>  y(2),dydx(2);

        ODE::dSpring<T> spring(0.7,0.01);
        x    = 0;
        y[1] = 1;
        y[2] = 0;
        saveTo(fp,x,y);
        for(size_t i=1;i<=np;++i)
        {
            const T x1 = x;
            const T x2 = x = (((T) (i) ) * x_end) / (T) np;
            odeint(y,x1,x2,dx1,spring,0,step);
            saveTo(fp,x,y);
        }
    }




}

Y_UTEST(ode_expl)
{
    TestExample<float>("f");
}
Y_UDONE()

