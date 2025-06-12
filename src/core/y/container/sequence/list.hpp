
//! \file

#ifndef Y_List_Included
#define Y_List_Included 1

#include "y/container/sequence.hpp"
#include "y/memory/io/limbo.hpp"
#include "y/core/linked/list.hpp"
#include "y/container/iter/linked.hpp"
#include "y/type/with-at-least.hpp"

namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //! Generic Node
        //
        //______________________________________________________________________
        template <typename T>
        class ListNode
        {
        public:
            Y_ARGS_DECL(T,Type); //!< aliases

            //! setup \param value content
            inline  ListNode(ParamType value) : next(0), prev(0), data(value) {}

            //! cleanup
            inline ~ListNode() noexcept {}

            //! normal access \return content
            inline Type &      operator*()       noexcept { return data; }

            //! const access \return const content
            inline ConstType & operator*() const noexcept { return data; }

            ListNode *next; //!< for list
            ListNode *prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(ListNode); //!< discarding
            MutableType data;                    //!< content

        };

    }

    //______________________________________________________________________
    //
    //
    //
    //! Generic List
    //
    //
    //______________________________________________________________________
    template <typename T,typename THREADING_POLICY = SingleThreadedClass>
    class List : public Sequence<T>, public THREADING_POLICY
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_DECL(T,Type);                                                      //!< aliases
        typedef typename THREADING_POLICY::Lock             Lock;                 //!< alias
        typedef Core::ListNode<Type>                        NodeType;             //!< alias
        typedef Core::ListOf<NodeType>                      ListType;             //!< alias
        typedef Memory::Limbo<NodeType,SingleThreadedClass> PoolType;             //!< alias
        typedef Iter::Linked<Iter::Forward,NodeType>        Iterator;             //!< alias
        typedef Iter::Linked<Iter::Forward,const NodeType>  ConstIterator;        //!< alias
        typedef Iter::Linked<Iter::Reverse,NodeType>        ReverseIterator;      //!< alias
        typedef Iter::Linked<Iter::Reverse,const NodeType>  ConstReverseIterator; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit List() : list(), pool() {}

        //! setup with capacity \param numItems minimal capacity
        inline explicit List(const WithAtLeast_ &, const size_t numItems) :
        list(), pool()
        {
            pool.cache(numItems);
        }

        //! cleanup
        inline virtual ~List() noexcept
        {
            release_();
        }

        //! forward display
        /**
         \param os output stream
         \param self *this
         \return os << self.list
         */
        inline friend std::ostream & operator<<(std::ostream &os, const List &self)
        {
            os << self.list;
            return os;
        }

        inline virtual size_t size() const noexcept
        {
            Y_Must_Lock();
            return list.size;
        }

        //! [DynamicContainer] 
        inline virtual size_t capacity() const noexcept
        {
            Y_Must_Lock();
            return list.size + pool.count();
        }

        inline virtual size_t available() const noexcept
        {
            Y_Must_Lock();
            return pool.count();
        }

        inline virtual void reserve(const size_t n)
        {
            Y_Must_Lock();
            pool.cache(n);
        }

        inline virtual void pushTail(ParamType value)
        {
            Y_Must_Lock();
            list.pushTail( pool.template conjure<ConstType>(value) );
        }

        inline virtual void popTail() noexcept
        {
            assert(list.size>0);
            Y_Must_Lock();
            pool.banish(list.popTail());
        }

        inline Iterator             begin()         noexcept { return list.head; } //!< \return iterator
        inline Iterator             end()           noexcept { return 0; }         //!< \return iterator

        inline ConstIterator        begin()   const noexcept { return list.head; } //!< \return const iterator
        inline ConstIterator        end()     const noexcept { return 0; }         //!< \return const iterator

        inline ReverseIterator      rbegin()        noexcept { return list.tail; } //!< \return reverse iterator
        inline ReverseIterator      rend()          noexcept { return 0; }         //!< \return reverse iterator

        inline ConstReverseIterator rbegin()  const noexcept { return list.tail; } //!< \return const reverse iterator
        inline ConstReverseIterator rend()    const noexcept { return 0; }         //!< \return const reverse iterator

    private:
        Y_Disable_Copy_And_Assign(List); //!< discarding
        ListType list;                   //!< list of live objects
        PoolType pool;                   //!< pool of zombis

        //! fast release
        inline void release_() noexcept {
            while(list.size>0) pool.remove(list.popTail());
            pool.release();
        }
    };

}

#endif
