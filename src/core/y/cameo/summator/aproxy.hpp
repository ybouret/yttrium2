
//! \file

#ifndef Y_Cameo_AProxySummator_Included
#define Y_Cameo_AProxySummator_Included 1

#include "y/cameo/summator/api.hpp"
#include "y/cameo/genus/aproxy.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        

        //______________________________________________________________________
        //
        //
        //
        //! use ap[n|z] to sum integral types
        //
        //
        //______________________________________________________________________
        template <typename T>
        class AProxySummator : public Summator<T>, public AProxyGenus
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
            inline AProxySummator() : Summator<T>(), acc()
            {
                Y_STATIC_CHECK(TypeTraits<T>::IsIntegral,NoIntegralType);
            }


            //! cleanup
            inline ~AProxySummator() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const AProxySummator &self)
            {
                return os << self.acc;
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual const char * callSign() const noexcept { return CallSign; }

            inline virtual void ldz() noexcept { acc.ldz(); }
            inline virtual T    sum()
            {
                T result = 0;
                if(!acc.tryCast(result))
                    Overflow();
                acc.ldz();
                return result;
            }


        private:
            Y_Disable_Copy_And_Assign(AProxySummator); //!< discarding
            CoreType acc;                              //!< inner accumulator

        protected:
            inline virtual void add(ParamType x) { acc += x; }

        };
    }

}

#endif


