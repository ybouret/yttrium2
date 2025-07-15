
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1

#include "y/cameo/selector.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"
#include "y/cameo/summator/fpoint.hpp"


namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Addition with API based on type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Addition : public Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API SummatorType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            inline explicit Addition() noexcept : SummatorType()  {}

            //! setup with summator accepting initializer \param n capacity
            inline explicit Addition(const size_t n) : SummatorType(n) {}

            //! cleanup
            inline virtual ~Addition() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Addition); //!< discarding
        };

    }

}

#endif
