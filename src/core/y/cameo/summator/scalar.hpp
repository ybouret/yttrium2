
//! \file

#ifndef Y_Cameo_ScalarSummator_Included
#define Y_Cameo_ScalarSummator_Included 1

#include "y/cameo/selector.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"
#include "y/cameo/summator/fpoint.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        template <typename T>
        class ScalarSummator : public Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API
        {
        public:
            typedef typename Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API SummatorType; //!< alias

            inline explicit ScalarSummator() : SummatorType()
            {
            }

            inline explicit ScalarSummator(const size_t n) : SummatorType(n) {}

            inline virtual ~ScalarSummator() noexcept
            {

            }

        private:
            Y_Disable_Copy_And_Assign(ScalarSummator);
        };
    }

}

#endif


