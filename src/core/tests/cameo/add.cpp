#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/apex/integer.hpp"
#include "y/utest/run.hpp"

#include "y/check/static.hpp"

using namespace Yttrium;

namespace Yttrium
{

    namespace Cameo
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

        //! ap[n|z|q]
        template <typename T>
        class DirectSummator : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);

            inline explicit DirectSummator() : Summator<T>(), acc()
            {
                Y_STATIC_CHECK(Y_Is_SuperSubClass_Strict(Apex::Number,MutableType),NoApexNumber);
            }

            inline virtual ~DirectSummator() noexcept
            {
            }

            inline virtual void ldz() noexcept { acc.ldz(); }

        private:
            Y_Disable_Copy_And_Assign(DirectSummator);
            MutableType acc;
        };


        template <typename T>
        class AProxySummator : public Summator<T>
        {
        public:
            typedef typename Pick<IsSigned<T>::Value,apz,apn>::Type CoreType;

            inline AProxySummator() : Summator<T>(), acc()
            {
                Y_STATIC_CHECK(TypeTraits<T>::IsIntegral,NoIntegralType);
            }

            inline ~AProxySummator() noexcept
            {

            }

            virtual void ldz() noexcept { acc.ldz(); }


        private:
            Y_Disable_Copy_And_Assign(AProxySummator);
            CoreType acc;
        };



    }


}

Y_UTEST(cameo_add)
{

    Cameo::DirectSummator<apz> zsum;
    Cameo::DirectSummator<apn> nsum;



}
Y_UDONE()



