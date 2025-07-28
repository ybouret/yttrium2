
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/apex/api/coven/iset.hpp"


namespace Yttrium
{

    namespace Coven
    {

        class Tribe
        {
        public:
            typedef Protean::WarpedCacheOf<Tribe,SingleThreadedClass> Cache;

            explicit Tribe(const IPool &pool,
                           const size_t n,
                           const size_t first) :
            basis(pool),
            ready(pool,n,first),
            next(0),
            prev(0)
            {
                basis << ready->popHead();
            }

            virtual ~Tribe() noexcept;

            friend std::ostream & operator<<(std::ostream &, const Tribe &);

            ISet    basis;
            IList   ready;
            Tribe * next;
            Tribe * prev;

        private:
            Y_Disable_Copy_And_Assign(Tribe);
        };

    }

}

#endif
 
