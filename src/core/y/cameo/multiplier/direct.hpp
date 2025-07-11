//! \file

#ifndef Y_Cameo_DirectMultiplier_Included
#define Y_Cameo_DirectMultiplier_Included 1


#include "y/cameo/multiplier/api.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Direct product for ap[n|z|q]
        //
        //
        //______________________________________________________________________
        template <typename T>
        class DirectMultiplier: public Multiplier<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit DirectMultiplier() : Multiplier<T>(), acc()
            {
                Y_STATIC_CHECK(Y_Is_SuperSubClass_Strict(Apex::Number,MutableType),NoApexNumber);
            }

            //! cleanup
            inline virtual ~DirectMultiplier() noexcept {}

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void ld1()     noexcept { acc.ld1(); }
            inline virtual T    product() noexcept
            {
                ConstType res = acc;
                ld1();
                return res;
            }

        private:
            Y_Disable_Copy_And_Assign(DirectMultiplier); //!< discarding
            MutableType acc; //!< accumulator

            inline virtual void mul(ParamType x) { acc *= x; }
            inline virtual void mul(ParamType x, size_t n) { while(n-- > 0) acc *= x; }
        };
    }
}

#endif


