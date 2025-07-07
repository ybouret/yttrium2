
//! \file

#ifndef Y_Cameo_AProxySummator_Included
#define Y_Cameo_AProxySummator_Included 1

#if 0
#include "y/cameo/summator/api.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        struct AProxySummatorInfo
        {
            static void Overflow();
        };

        template <typename T>
        class AProxySummator : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);
            typedef typename Pick<IsSigned<T>::Value,apz,apn>::Type CoreType;

            inline AProxySummator() : Summator<T>(), acc()
            {
                Y_STATIC_CHECK(TypeTraits<T>::IsIntegral,NoIntegralType);
            }

            inline ~AProxySummator() noexcept
            {

            }

            virtual void ldz() noexcept { acc.ldz(); }

            inline virtual T sum()
            {
                T result = 0;
                if(!acc.tryCast(result))
                    AProxySummatorInfo::Overflow();
                acc.ldz();
                return result;
            }


        private:
            Y_Disable_Copy_And_Assign(AProxySummator);
            CoreType acc;

            inline virtual void add(ParamType x) { acc += x; }

        };
    }

}

#endif

#endif

