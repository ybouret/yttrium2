
//! \file

#ifndef Y_Protean_ListProto_Included
#define Y_Protean_ListProto_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Protean
    {

        //! helper to setup same parts of ListProto
#define Y_Protean_List_Proto()          \
/**/   CONTAINER(),                     \
/**/   ThreadingPolicy(),               \
/**/   Ingress< Core::ListOf<NODE> >(), \
/**/   list()


        //______________________________________________________________________
        //
        //
        //
        //! Prototype with common methods
        //
        //
        //______________________________________________________________________
        template <
        typename NODE,
        typename POOL,
        typename CONTAINER,
        typename ThreadingPolicy>
        class ListProto :
        public CONTAINER,
        public ThreadingPolicy,
        public Ingress< Core::ListOf<NODE> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Core::ListOf<NODE>             ListType;  //!< alias
            typedef POOL                           PoolType;  //!< alias
            typedef Ingress<ListType>              Entrance;  //!< alias
            typedef typename NODE::Type            Type;      //!< alias
            typedef typename NODE::ConstType       ConstType; //!< alias
            typedef typename NODE::ParamType       ParamType; //!< alias
            typedef typename ThreadingPolicy::Lock Lock;      //!< alias


            //__________________________________________________________________
            //
            //
            // Interface/Methods
            //
            //__________________________________________________________________

            //! append new node \param args for node constructor
            inline virtual void pushTail(ParamType args)
            {
                Y_Must_Lock();
                list.pushTail( pool.summon(args) );
            }

            //! preprend new node \param args for node constructor
            inline void pushHead(ParamType args)
            {
                Y_Must_Lock();
                list.pushHead( pool.summon(args) );
            }

            //! remove head node
            inline void popHead() noexcept
            {
                assert(list.size>0);
                Y_Must_Lock();
                pool.banish( list.popHead() );
            }

            //! remove tail node
            inline void popTail() noexcept
            {
                assert(list.size>0);
                Y_Must_Lock();
                pool.banish( list.popTail() );
            }

            //! \return live objects
            virtual size_t size() const noexcept { return list.size; }


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~ListProto() noexcept { release_(); }
        protected:

            //! setup with own cache
            inline explicit ListProto() :
            Y_Protean_List_Proto(), pool()
            {}

            //! setup with shared cache
            inline explicit ListProto(const PoolType &shared) :
            Y_Protean_List_Proto(), pool(shared)
            {}

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            ListType list; //!< live nodes
            PoolType pool; //!< zombi nodes

            //__________________________________________________________________
            //
            //
            // Other Methods
            //
            //__________________________________________________________________
        protected:

            //! release all data
            inline void release_() noexcept {
                Y_Must_Lock();
                while(list.size>0) pool.remove( list.popTail() );
                pool.release();
            }

            inline void duplicate(const ListProto &other)
            {
                volatile Lock primary(*this), replica(other);
                try {
                    for(const NODE *node=other->head;node;node=node->next)
                        list.pushTail( pool.mirror(node) );
                }
                catch(...) { release_(); throw; }
            }

            inline void xch(ListProto &other) noexcept
            {
                volatile Lock primary(*this), replica(other);
                list.swapListFor(other.list);
            }

        private:
            Y_Disable_Copy_And_Assign(ListProto); //!< discaring
            inline virtual typename Entrance::ConstInterface & locus() const noexcept { return list; }

        };

    }

}

#endif

