
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
                Y_OSTREAM_PROTO(Broken);

                static SignType Compare(const Broken &, const Broken &) noexcept;

                const Law &law; //!< broken law
                xreal_t    xs;  //!< law excess
                xreal_t    dc;  //!< xs/law.norm = |delta C|

            private:
                Y_Disable_Assign(Broken);
            };

            typedef List<Broken>    BList;
            typedef BList::NodeType BNode;


        }

    }

}

#endif

