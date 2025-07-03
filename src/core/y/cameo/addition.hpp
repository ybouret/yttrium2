
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

        template <typename T>
        class Addition : public Select<T,DirectSummator,AProxySummator,FPointSummator>::API
        {
        public:
            explicit Addition() noexcept {}
            virtual ~Addition() noexcept {}
            
        private:
            Y_Disable_Copy_And_Assign(Addition);
        };

    }

}

#endif
