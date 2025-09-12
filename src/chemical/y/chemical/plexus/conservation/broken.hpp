
//! \file


#ifndef Y_Chemical_Conservation_Broken_Included
#define Y_Chemical_Conservation_Broken_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/protean/solo/heavy/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            class Broken
            {
            public:
                Broken(const Law &, const xreal_t) noexcept;
                ~Broken() noexcept;
                Broken(const Broken &) noexcept;

                const Law &law;
                xreal_t    xs;

            private:
                Y_Disable_Assign(Broken);
            };

            typedef List<Broken>    BList;
            typedef BList::NodeType BNode;


        }

    }

}

#endif

