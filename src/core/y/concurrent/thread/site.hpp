//! \file

#ifndef Y_Concurrent_Thread_Site_Included
#define Y_Concurrent_Thread_Site_Included 1

#include "y/protean/bare/heavy/list.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef Protean::BareHeavyList<size_t> PList;
        typedef PList::NodeType                PNode;

        class Site : public Ingress<const PList>
        {
        public:

            Site();
            Site(const Site &);
            virtual ~Site() noexcept;

        private:
            Y_Ingress_Decl();
            PList plist;
        };

    }
}

#endif // !Y_Concurrent_Thread_Site_Included

