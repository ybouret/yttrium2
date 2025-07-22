

//! \file

#ifndef Y_Cameo_Multiplication_Included
#define Y_Cameo_Multiplication_Included 1

#include "y/cameo/selector.hpp"
#include "y/cameo/multiplier/direct.hpp"
#include "y/cameo/multiplier/aproxy.hpp"
#include "y/cameo/multiplier/fpoint.hpp"


namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Multiplication with API based on type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Multiplication : public Select<T,DirectMultiplier<T>,AProxyMultiplier<T>,FPointMultiplier<T> >::API
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename Select<T,DirectMultiplier<T>,AProxyMultiplier<T>,FPointMultiplier<T> >::API MultiplierType; //!< alias
            Y_Args_Declare(T,Type);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            explicit Multiplication() noexcept : MultiplierType()  {}

            //! cleanup
            virtual ~Multiplication() noexcept {}

            inline Multiplication & operator=(ParamType value) { this->ld1(); this->mul(value); return *this; }


        private:
            Y_Disable_Copy_And_Assign(Multiplication); //!< discarding
        };

    }

}

#endif
