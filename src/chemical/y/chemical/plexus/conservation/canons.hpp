
//! \file


#ifndef Y_Chemical_Conservation_Canons_Included
#define Y_Chemical_Conservation_Canons_Included 1


#include "y/chemical/plexus/conservation/canon.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Canons : public Object, public Ingress< const Canon::List >
            {
            public:
                explicit Canons(XMLog &xml, const Laws &laws);
                virtual ~Canons() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Canons);
                Y_Ingress_Decl();
                Canon::List clist;
                Canon *accepted(const Law &) noexcept;
            };

        }

    }

}

#endif
