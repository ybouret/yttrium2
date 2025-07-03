//! \file

#ifndef Y_Cameo_DirectSummator_Included
#define Y_Cameo_DirectSummator_Included 1

#include "y/cameo/summator.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Cameo
    {
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

            inline virtual void add(ConstType & x) { acc += x; }
        };
    }
}

#endif

