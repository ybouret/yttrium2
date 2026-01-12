
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
            typedef Core::ListOf<NODE>                     ListType;             //!< alias
            typedef POOL                                   PoolType;             //!< alias
            typedef Ingress<ListType>                      Entrance;             //!< alias
            typedef typename NODE::Type                    Type;                 //!< alias
            typedef typename NODE::ConstType               ConstType;            //!< alias
            typedef typename NODE::ParamType               ParamType;            //!< alias
            typedef typename NODE::ReturnType              ReturnType;           //!< alias
            typedef typename ThreadingPolicy::Lock         Lock;                 //!< alias
            typedef Iter::Linked<Iter::Forward,NODE>       Iterator;             //!< alias
            typedef Iter::Linked<Iter::Forward,const NODE> ConstIterator;        //!< alias
            typedef Iter::Linked<Iter::Reverse,NODE>       ReverseIterator;      //!< alias
            typedef Iter::Linked<Iter::Reverse,const NODE> ConstReverseIterator; //!< alias

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

            //! \param args argument \return new/existing tail node set to args
            inline NODE * query(ParamType args)
            {
                Y_Must_Lock();
                if(list.size) {
                    **list.tail = args;
                    return list.popTail();
                }
                else
                {
                    return pool.summon(args);
                }
            }


            //! push tail item with two args constructor
            /**
             \param u first arg
             \param v second arg
             */
            template <typename U, typename V> inline
            void pushTail(U &u, V &v)
            {
                Y_Must_Lock();
                list.pushTail( pool.summon(u,v) );
            }

            //! push head item with two args constructor
            /**
             \param u first arg
             \param v second arg
             */
            template <typename U, typename V> inline
            void pushHead(U &u, V &v)
            {
                Y_Must_Lock();
                list.pushHead( pool.summon(u,v) );
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

            //! remove tail node \return tail value
            inline ReturnType pullTail()
            {
                assert(list.size>0);
                Y_Must_Lock();
                ReturnType res = **list.tail;
                pool.banish( list.popTail() );
                return res;
            }

            //! remove tail node \return head value
            inline ReturnType pullHead()
            {
                assert(list.size>0);
                Y_Must_Lock();
                ReturnType res = **list.head;
                pool.banish( list.popHead() );
                return res;
            }

            //! pop and banish node from list \param node owned node
            inline void cut(NODE * const node) noexcept
            {
                assert(node); assert(list.owns(node));
                Y_Must_Lock();
                pool.banish( list.pop(node) );
            }



            //! \return live objects
            inline virtual size_t size() const noexcept { return list.size; }


            //! append \param rhs value \return *this
            inline ListProto & operator<<(ParamType rhs)
            {
                pushTail(rhs);
                return *this;
            }

            //! prepend \param lhs value \return *this
            inline ListProto & operator>>(ParamType lhs)
            {
                pushHead(lhs);
                return *this;
            }

            //! append copy \param other another list \return *this
            inline ListProto & operator<<(const ListProto &other)
            {
                ListType temp; duplicateInto(temp,other);
                list.mergeTail(temp);
                return *this;
            }

            inline Iterator             begin()  noexcept       { return list.head; } //!< \return matching iterator
            inline Iterator             end()    noexcept       { return 0;         } //!< \return matching iterator
            inline ConstIterator        begin()  const noexcept { return list.head; } //!< \return matching iterator
            inline ConstIterator        end()    const noexcept { return 0;         } //!< \return matching iterator
            inline ReverseIterator      rbegin() noexcept       { return list.tail; } //!< \return matching iterator
            inline ReverseIterator      rend()   noexcept       { return 0;         } //!< \return matching iterator
            inline ConstReverseIterator rbegin() const noexcept { return list.tail; } //!< \return matching iterator
            inline ConstReverseIterator rend()   const noexcept { return 0;         } //!< \return matching iterator


            //! \param args parameter \return true if found from list head
            inline bool found(ParamType args) const
            {
                for(const NODE *node=list.head;node;node=node->next)
                {
                    if( NODE::Same(args,**node) ) return true;
                }
                return false;
            }

            //! \param args argument to add only if not present \return *this
            inline ListProto & operator |= (ParamType args)
            {
                if(!found(args)) pushTail(args);
                return *this;
            }

            //! \param other list to add elements from only if not present \return *this
            template <
            typename _POOL,
            typename _CONTAINER,
            typename _POLICY>
            inline ListProto & operator |= (const ListProto<NODE,_POOL,_CONTAINER,_POLICY> &other)
            {
                ListProto &self = *this;
                for(const NODE *node=other->head;node;node=node->next)
                {
                    self |= **node;
                }
                return self;
            }



            //! exchange contents \param other another list
            inline void xch( ListProto &other ) noexcept
            {
                list.swapListFor(other.list);
            }

            //! sort \param proc comparing node content
            template <typename COMPARE_DATA> inline
            void sort(COMPARE_DATA &proc) noexcept
            {
                list.sortWith(proc);
            }

            //! remove undesired components \param isBad detect bad component
            template <typename IS_BAD> inline
            void removeIf(IS_BAD &isBad)
            {
                ListType kept;
                while(list.size)
                {
                    if( isBad( **list.head) )
                        popHead();
                    else
                        kept.pushTail( list.popHead() );
                }
                list.swapListFor(kept);
            }



            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~ListProto() noexcept { releaseList_(); }
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

            //! free all content into pool
            inline void freeList_() noexcept
            {
                Y_Must_Lock();
                while( list.size ) pool.banish( list.popTail() );
            }

            //! release all data thru pool
            inline void releaseList_() noexcept {
                Y_Must_Lock();
                while(list.size>0) pool.remove( list.popTail() );
            }


            //! duplicate into agnostic list
            /**
             \param target list to fill
             \param source list to copy
             */
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
                    while(target.size>0) pool.remove( target.popTail() );
                    throw;
                }
            }

            //! duplicate \param other another list
            inline void duplicate(const ListProto &other)
            {
                volatile Lock primary(*this), replica(other);
                assert(0==list.size);
                duplicateInto(list,other);
            }



        private:
            Y_Disable_Copy_And_Assign(ListProto); //!< discaring
            inline virtual typename Entrance::ConstInterface & locus() const noexcept { return list; }

            //! [Sequence] \return head value
            inline virtual ConstType & getHead() const noexcept
            {
                Y_Must_Lock();
                assert(list.head!=0);
                return **list.head;
            }

            //! [Sequence] \return tail value
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

