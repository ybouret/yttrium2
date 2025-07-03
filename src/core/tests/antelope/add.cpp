#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace Yttrium
{

    namespace AntElOp
    {
        template <typename T>
        class Summator
        {
        public:
            Y_Args_Declare(T,Type);
        protected:
            inline explicit Summator() noexcept {}
        public:
            inline virtual ~Summator() noexcept {}

            virtual void ldz() noexcept = 0;


        private:
            Y_Disable_Copy_And_Assign(Summator);
        };

        template <typename T>
        class DirectSummator; //!< ap[n|z|q]

        class AProxySummator; //!< integral types : ap[n|z]

    }


}

Y_UTEST(antelope_add)
{
    std::cerr << MKL::Pythagoras<float>(3,4) << std::endl;

    {
        Complex<long double> z(3,4);
        std::cerr << z.abs() << std::endl;
    }

    {
        Complex< XReal<double> > z(3,4);
        std::cerr << z.abs() << std::endl;

    }



    std::cerr << MKL::Pythagoras<float>(-5,4,-1) << std::endl;


}
Y_UDONE()



