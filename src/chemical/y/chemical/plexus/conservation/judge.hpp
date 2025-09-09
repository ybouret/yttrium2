

//! \file


#ifndef Y_Chemical_Conservation_Judge_Included
#define Y_Chemical_Conservation_Judge_Included 1


#include "y/chemical/plexus/conservation/laws.hpp"
#include "y/protean/coop/heavy/list.hpp"
#include "y/ortho/house.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {


            class Broken
            {
            public:

                Broken(const Law & _law, const xreal_t _xs) noexcept;
                Broken(const Broken &) noexcept;
                ~Broken() noexcept;
                Y_OSTREAM_PROTO(Broken);
                
                const Law &law;
                xreal_t    xs;
            };

            typedef Protean::CoopHeavyList<Broken> BList;
            typedef BList::NodeType                BNode;
            typedef BList::PoolType                BPool;

            class Judge : public Object
            {
            public:
                explicit Judge(const Laws &);
                virtual ~Judge() noexcept;

                void abide(XMLog &xml, XWritable &Ctop);


            private:
                Y_Disable_Copy_And_Assign(Judge);
                const Laws &  laws;
                const xreal_t zero;
                BPool         bpool;
                BList         blist;
                BList         basis;
                Ortho::House  house;
                XAdd          xadd;
            };
        }

    }

}

#endif

