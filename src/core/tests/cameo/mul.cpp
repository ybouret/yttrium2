
#include "y/cameo/multiplier/aproxy.hpp"
#include "y/cameo/multiplier/direct.hpp"
#include "y/cameo/multiplier/synod/fp-list.hpp"


#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"
#include <cmath>

using namespace Yttrium;

namespace Yttrium
{
    namespace Cameo
    {

     
         
       


        template <typename T>
        class FPointMultiplier : public Multiplier<T>
        {
        public:
            Y_Args_Declare(T,Type);

            typedef Synod::FPList<T>              EngineType;
            typedef typename EngineType::UnitList UnitList;

            inline explicit FPointMultiplier() : Multiplier<T>(), engine()
            {
            }

            inline virtual ~FPointMultiplier() noexcept {
            }

            inline Caching *       operator->()       noexcept { return &engine; }
            inline const Caching * operator->() const noexcept { return &engine; }

            inline const UnitList & operator*() const noexcept { return *engine; }

            inline virtual void ldz() noexcept { engine.free(); }

            inline virtual T product()
            {
                return engine.product();
            }

        private:
            EngineType engine;

            virtual void mul(ParamType x)           { engine.push(x);   }
            virtual void mul(ParamType x, size_t n) { engine.push(x,n); }
        };

    }
}


namespace
{
    template <typename T> static inline
    void showMass(const T &x)
    {
        std::cerr << x << " => " << Cameo::GetFPointMass(x) << std::endl;
    }

}

Y_UTEST(cameo_mul)
{
    {
        Cameo::DirectMultiplier<apn> nmul;
        Cameo::DirectMultiplier<apz> zmul;
        Cameo::DirectMultiplier<apq> qmul;
    }

    {
        Cameo::AProxyMultiplier<int>      imul;
        Cameo::AProxyMultiplier<uint16_t> umul;
    }

    {
        const float       f = 0.1f;  showMass(f);
        const double      d = -1e-8; showMass(d);
        const long double D = 1e43;  showMass(D);
    }

    {
        const XReal<float>       f = 0.1;   showMass(f);
        const XReal<double>      d = -1e-8; showMass(d);
        const XReal<long double> D = 1e43;  showMass(D);
    }

    {
        const Complex<float>           f(0.1,0.2);   showMass(f);
        const Complex< XReal<double> > d(1e-8,1e-5); showMass(d);
    }


    {
        Cameo::FPointMultiplier<float> fmul;
        fmul << 1e-5f << 1e-8f << 0.1f;
        std::cerr << *fmul << std::endl;
        std::cerr << fmul.product() << std::endl;
    }

}
Y_UDONE()
