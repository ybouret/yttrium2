

//! \file


#ifndef Y_Chemical_Conservation_Laws_Included
#define Y_Chemical_Conservation_Laws_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/stream/xmlog.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Laws : public Object, public Ingress< const Core::ListOf<Law> >, public Assembly
            {
            public:
                explicit Laws(XMLog &, const uMatrix &, const SList &);
                virtual ~Laws() noexcept;


            private:
                Y_Disable_Copy_And_Assign(Laws);
                Y_Ingress_Decl();
                CxxListOf<Law> list;
            };

        }

    }

}

#endif

