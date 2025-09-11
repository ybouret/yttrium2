//! \file


#ifndef Y_Chemical_Conservation_Act_Included
#define Y_Chemical_Conservation_Act_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/reactive/equilibrium.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Act : public Object, public Ingress< const LList >
            {
            public:
                typedef CxxListOf<Act> List;

                explicit Act(const Law &first);
                virtual ~Act() noexcept;

                bool accepts(const Law &) const noexcept;
                void connect(const Law &);
                void combine(Act &);

            private:
                Y_Disable_Copy_And_Assign(Act);
                Y_Ingress_Decl();


                LList  list;
            public:
                const SList slist;
                const EList elist;
                Act *next;
                Act *prev;
            };
        }

    }

}

#endif


