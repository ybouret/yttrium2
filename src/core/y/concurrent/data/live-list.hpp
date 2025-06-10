
//! \file

#ifndef Y_Concurrent_Live_List_Included
#define Y_Concurrent_Live_List_Included 1

#include "y/core/linked/list.hpp"
#include "y/type/ingress.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        template <typename NODE>
        class LiveList :
        public Ingress<const Core::ListOf<NODE> >,
        public Releasable
        {
        public:
            typedef Core::ListOf<NODE>      CoreList;
            typedef Ingress<const CoreList> CoreListAPI;

            explicit LiveList() noexcept : CoreListAPI(), my() {}
            virtual ~LiveList() noexcept { release_(); }

        private:
            Y_Disable_Assign(LiveList);
            CoreList my;

            inline void release_() noexcept
            {
                
            }
        };

    }
}

#endif
