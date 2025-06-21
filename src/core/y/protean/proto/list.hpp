
//! \file

#ifndef Y_Protean_ListProto_Included
#define Y_Protean_ListProto_Included 1

#include "y/core/setup.hpp"
#include "y/core/linked/list.hpp"
#include "y/threading/must-lock.hpp"
#include "y/type/ingress.hpp"
#include "y/container/iter/linked.hpp"

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
            typedef Iter::Linked<Iter::Forward,NODE>       Iterator;
            typedef Iter::Linked<Iter::Forward,const NODE> ConstIterator;
            typedef Iter::Linked<Iter::Reverse,NODE>       ReverseIterator;
            typedef Iter::Linked<Iter::Reverse,const NODE> ConstReverseIterator;

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


            inline ListProto & operator<<(ParamType rhs)
            {
                pushTail(rhs);
                return *this;
            }

            inline ListProto & operator>>(ParamType lhs)
            {
                pushHead(lhs);
                return *this;
            }

            inline Iterator             begin()  noexcept       { return list.head; }
            inline Iterator             end()    noexcept       { return 0;         }
            inline ConstIterator        begin()  const noexcept { return list.head; }
            inline ConstIterator        end()    const noexcept { return 0;         }
            inline ReverseIterator      rbegin() noexcept       { return list.tail; }
            inline ReverseIterator      rend()   noexcept       { return 0;         }
            inline ConstReverseIterator rbegin() const noexcept { return list.tail; }
            inline ConstReverseIterator rend()   const noexcept { return 0;         }
            
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

            //! setup with shared cache \param shared existing cache
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


            inline void duplicateInto(ListType &target, const ListProto &source)
            {
                volatile Lock primary(*this), replica(source);
                assert(0==target.size);
                try {
                    for(const NODE *node=source->head;node;node=node->next)
                        list.pushTail( pool.mirror(node) );
                }
                catch(...)
                {
                    while(target.size>0) pool.banish( target.popTail() );
                    throw;
                }
            }

            inline void duplicate(const ListProto &other)
            {
                volatile Lock primary(*this), replica(other);
                assert(0==list.size);
                try { duplicateInto(list,other); }
                catch(...) { release_(); throw;  }
            }



        private:
            Y_Disable_Copy_And_Assign(ListProto); //!< discaring
            inline virtual typename Entrance::ConstInterface & locus() const noexcept { return list; }

            inline virtual ConstType & getHead() const noexcept
            {
                Y_Must_Lock();
                assert(list.head!=0);
                return **list.head;
            }

            inline virtual ConstType & getTail() const noexcept
            {
                Y_Must_Lock();
                assert(list.tail!=0);
                return **list.tail;
            }
        };

    }

}

#endif

