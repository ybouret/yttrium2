
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/apex/api/coven/iset.hpp"
#include "y/apex/api/ortho/family.hpp"

#define Y_Coven_Stamp 1

namespace Yttrium
{

    namespace Coven
    {

        class Tribe
        {
        public:
            typedef Protean::WarpedCacheOf<Tribe,SingleThreadedClass> Cache;
            typedef Core::ListOf<Tribe> List;
            typedef const Tribe & ParamType; //!< for Cache declaration

            explicit Tribe(const IPool &pool,
                           const size_t n,
                           const size_t first) :
            basis(pool),
            ready(pool,n,first),
#if Y_Coven_Stamp
            stamp(pool),
#endif
            next(0),
            prev(0)
            {
                basis << ready->popHead();
                stamp << first;
            }

            explicit Tribe(const Tribe &tribe,
                           const size_t shift) :
            basis(tribe.basis),
            ready(tribe.ready),
#if Y_Coven_Stamp
            stamp(tribe.stamp),
#endif
            next(0),
            prev(0)
            {
                INode * const node = ready->fetch(shift);
#if Y_Coven_Stamp
                stamp << **node;
#endif
                basis << ready->pop( node );
            }


            virtual ~Tribe() noexcept;

            friend std::ostream & operator<<(std::ostream &, const Tribe &);


            inline void generate(Tribe::List &heirs, Cache &cache) const
            {
                size_t       ir = 1;
                for(const INode *node=ready->head;node;node=node->next,++ir)
                {
                    Tribe * const tr = heirs.pushTail( cache.summon(*this,ir) );
                    std::cerr << *tr << std::endl;
                }
            }

            ISet    basis;
            IList   ready;
#if Y_Coven_Stamp
            IList   stamp;
#endif
            Tribe * next;
            Tribe * prev;

        private:
            Y_Disable_Copy_And_Assign(Tribe);
        };

    }

}

#endif
 
