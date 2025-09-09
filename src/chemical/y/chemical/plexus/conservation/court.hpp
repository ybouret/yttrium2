
//! \file


#ifndef Y_Chemical_Conservation_Court_Included
#define Y_Chemical_Conservation_Court_Included 1


#include "y/chemical/plexus/conservation/judge.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Court : public Ingress< const Core::ListOf<Judge> >
            {
            public:
                explicit Court(const Clusters &);
                virtual ~Court() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Court);
                Y_Ingress_Decl();
                CxxListOf<Judge> judges;
            };
        }

    }

}

#endif
