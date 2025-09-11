//! \file


#ifndef Y_Chemical_Conservation_Canon_Included
#define Y_Chemical_Conservation_Canon_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Canon : public Object, public Ingress< const LList >
            {
            public:
                typedef CxxListOf<Canon> List;
                
                explicit Canon(const Law &first);
                virtual ~Canon() noexcept;

                bool accepts(const Law &) const noexcept;
                void connect(const Law &);
                void combine(Canon &);

            private:
                Y_Disable_Copy_And_Assign(Canon);
                Y_Ingress_Decl();


                LList  list;
            public:
                const SList slist;
                const EList elist;
                Canon *next;
                Canon *prev;
            };
        }

    }

}

#endif


