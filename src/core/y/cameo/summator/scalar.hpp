
//! \file

#ifndef Y_Cameo_ScalarSummator_Included
#define Y_Cameo_ScalarSummator_Included 1

#include "y/cameo/selector.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"
#include "y/cameo/summator/fpoint.hpp"
#include "y/mkl/api/adaptor.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Choose summator for scalar type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class ScalarSummator : public Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases
            typedef typename Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API SummatorType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! default constructor
            inline explicit ScalarSummator() : SummatorType() { }

            //! optional for FPointSummator \param n minimal capacity
            inline explicit ScalarSummator(const size_t n) : SummatorType(n) {}

            //! cleanup
            inline virtual ~ScalarSummator() noexcept  {}

          


        private:
            Y_Disable_Copy_And_Assign(ScalarSummator); //!< discaring
        };
    }

}

#endif // !Y_Cameo_ScalarSummator_Included


