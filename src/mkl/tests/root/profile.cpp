
#include "y/mkl/root/zbis.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/random/park-miller.hpp"
#include <cfloat>
#include "y/string/format.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    static double       C0    = 0.001;
    static const double LamAH = 0.55;
    static const double LamAm = 1.0-LamAH;

    static const double Kw = 1e-14;
    static const double Ka = pow(10.0,-5.2);

    static
    double getAm(const double h)
    {
        return Ka/(Ka+h) * C0;
    }

    static
    double getAH(const double h)
    {
        return h/(Ka+h) * C0;
    }

    static double getLambda(const double h)
    {
        return LamAH * getAH(h) + LamAm * getAm(h);
    }

    static
    double getQ(const double h)
    {
        return -(h-Kw/h-getAm(h));
    }

    static const double pH0 = 6;
    static const double pH1 = 8;
    static const double h0  = pow(10.0,-pH0);
    static const double h1  = pow(10.0,-pH1);
    static double Q0        = 0;
    static double Q1        = 0;
    static double Lambda0   = 0;
    static double Lambda1   = 0;

    //! setup for a given C0
    static void setup()
    {
        Q0 = getQ(h0);
        Q1 = getQ(h1);
        Lambda0 = getLambda(h0);
        Lambda1 = getLambda(h1);
    }

    static double u = 0.0;

    static double Eq(const double h)
    {
        const double v      = 1.0-u;
        const double Q      = v * Q0 + u * Q1;
        const double Lambda = v * Lambda0 + u * Lambda1;

        return h*h - Kw + h*( -Ka/(LamAH * h + Ka * LamAm) * Lambda + Q);
    }

    static double compute_h(const double uu)
    {
        ZRid<double>       solve;
        u = uu;
        Triplet<double> x = { 0,0,1};
        Triplet<double> f = { Eq(x.a), 0, Eq(x.c) };
        return solve(Eq,x,f);
    }

    static inline void save(const double c)
    {
        C0 = c;
        setup();
        const String fileName = Formatted::Get("profile%.0e.dat",C0);
        OutputFile   fp(fileName);
        const unsigned np = 200;
        for(unsigned i=0;i<=np;++i)
        {
            const double uu = double(i)/np;
            const double h = compute_h( uu );
            fp("%.15g %.15g\n",uu, -log10(h) );
        }

    }

}

Y_UTEST(root_profile)
{

    Random::ParkMiller ran;

    {
        C0 = 0;
        setup();
        std::cerr << "h0=" << compute_h(0) << std::endl;
        std::cerr << "h1=" << compute_h(1) << std::endl;
    }

    save(0.0);
    save(1e-6);
    save(1e-5);
    save(1e-4);
    save(1e-3);
    save(1e-2);



}
Y_UDONE()

