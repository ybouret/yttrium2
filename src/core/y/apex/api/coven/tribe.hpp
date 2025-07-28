
//! \file

#ifndef Y_Coven_Tribe_Included
#define Y_Coven_Tribe_Included 1

#include "y/apex/api/coven/carrier.hpp"

#define Y_Coven_Stamp 1

namespace Yttrium
{

    namespace Coven
    {




#if 0
        class Tribe
        {
        public:
            typedef Protean::WarpedCacheOf<Tribe,SingleThreadedClass> Cache;
            typedef Core::ListOf<Tribe> List;
            typedef const Tribe & ParamType; //!< for Cache declaration

            template <typename MATRIX>
            struct Context
            {
                const MATRIX & mu; //!< matrix to explore
                IPool &        ip; //!< index pool for indices
                Tribe::Cache & tc; //!< tribe cache
                Carrier &      cr; //!< carrier for mu.cols
            };


            //! prepare family from first vector
            /**
             \param ctx   matrix and memory
             \param first index
             */
            template <typename MATRIX>
            explicit Tribe(Context<MATRIX> &ctx,
                           const size_t     first) :
            basis(ctx.ip),
            ready(ctx.ip,ctx.mu.rows,first),
#if Y_Coven_Stamp
            stamp(ctx.ip),
#endif
            fpool(ctx.cr.fpool),
            family( fpool.query() ),
            next(0),
            prev(0)
            {

                try
                {

                    basis << ready->popHead();
#if Y_Coven_Stamp
                    stamp << first;
#endif
                    QVector * const v = family->accepts(ctx.mu[first]);
                    if(v) family->progeny(v);
                    assert(v == family->lastVec );
                }
                catch(...) { quit(); throw; }
            }

            template <typename MATRIX>
            explicit Tribe(const MATRIX & mu,
                           const Tribe &  tribe,
                           const size_t   shift) :
            basis(tribe.basis),
            ready(tribe.ready),
#if Y_Coven_Stamp
            stamp(tribe.stamp),
#endif
            fpool(tribe.fpool),
            family( fpool.query(*tribe.family) ),
            next(0),
            prev(0)
            {
                try
                {
                    INode * const node = ready->fetch(shift); // get ready node
                    const size_t  indx = **node;              // get indx
#if Y_Coven_Stamp
                    stamp << indx;
#endif
                    basis << ready->pop( node );              // transfer into basis
                }
                catch(...) { quit(); throw; }
            }

            virtual ~Tribe() noexcept;

            friend std::ostream & operator<<(std::ostream &, const Tribe &);


#if 0
            inline void generate(Tribe::List &heirs,
                                 Cache &      cache) const
            {
                size_t       ir = 1;
                for(const INode *node=ready->head;node;node=node->next,++ir)
                {
                    Tribe * const tr = heirs.pushTail( cache.summon(*this,ir) );
                    std::cerr << *tr << std::endl;
                }
            }
#endif

            void remove(const size_t indx) noexcept;


            ISet           basis;
            IList          ready;
#if Y_Coven_Stamp
            IList          stamp;
#endif
            QFamily::Pool & fpool;
            QFamily * const family;
            Tribe *         next;
            Tribe *         prev;

        private:
            Y_Disable_Copy_And_Assign(Tribe);
            void quit() noexcept;
        };
#endif
        
    }

}

#endif
 
