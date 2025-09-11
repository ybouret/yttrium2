
//! \file


#ifndef Y_Chemical_Conservation_Acts_Included
#define Y_Chemical_Conservation_Acts_Included 1


#include "y/chemical/plexus/conservation/act.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Acts : public Object, public Ingress< const Act::List >
            {
            public:
                explicit Acts(XMLog &xml, const Laws &laws);
                virtual ~Acts() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Acts);
                Y_Ingress_Decl();
                Act::List clist;
                Act *accepted(const Law &) noexcept;
            };

        }

    }

}

#endif
