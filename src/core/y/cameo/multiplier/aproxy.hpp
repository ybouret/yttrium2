
//! \file

#ifndef Y_Cameo_AProxyMultiplier_Included
#define Y_Cameo_AProxyMultiplier_Included 1

#include "y/cameo/multiplier/api.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! common info for AProxyMultiplier
        //
        //
        //______________________________________________________________________
        struct AProxyMultiplierInfo
        {
            static void Overflow(); //!< overflow when type casting
        };

        //______________________________________________________________________
        //
        //
        //
        //! use ap[n|z] to sum integral types
        //
        //
        //______________________________________________________________________
        template <typename T>
        class AProxyMultiplier : public Multiplier<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases
            typedef typename Pick<IsSigned<T>::Value,apz,apn>::Type CoreType; //!< Apex matching type

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline AProxyMultiplier() : Multiplier<T>(), acc()
            {
                Y_STATIC_CHECK(TypeTraits<T>::IsIntegral,NoIntegralType);
            }


            //! cleanup
            inline ~AProxyMultiplier() noexcept {}

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void ld1() noexcept { acc.ld1(); }
            inline virtual T    product()
            {
                T result = 0;
                if(!acc.tryCast(result))
                    AProxyMultiplierInfo::Overflow();
                ld1();
                return result;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return internal accumulator, mostly to debug
            inline const CoreType operator*() const noexcept { return acc; }

        private:
            Y_Disable_Copy_And_Assign(AProxyMultiplier); //!< discarding
            CoreType acc;                              //!< inner accumulator

        protected:
            inline virtual void mul(ParamType x)
            {
                acc *= x;
            }
            inline virtual void mul(ParamType x, size_t n)
            {
                const CoreType _(x);
                while(n-- > 0) acc *= _;
            }

        };
    }

}

#endif


