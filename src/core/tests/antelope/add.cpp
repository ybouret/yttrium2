#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/apex/integer.hpp"
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

        //!< ap[n|z|q]
        template <typename T>
        class DirectSummator : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);

            inline explicit DirectSummator() : Summator<T>(), acc()
            {
            }

            inline virtual ~DirectSummator() noexcept
            {
            }

            inline virtual void ldz() noexcept { acc.ldz(); }

        private:
            Y_Disable_Copy_And_Assign(DirectSummator);
            MutableType acc;
        };


        class AProxySummator; //!< integral types : ap[n|z]



    }


}

Y_UTEST(antelope_add)
{

    AntElOp::DirectSummator<apz> zsum;



}
Y_UDONE()



