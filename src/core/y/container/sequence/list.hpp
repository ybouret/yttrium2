
//! \file

#ifndef Y_List_Included
#define Y_List_Included 1

#include "y/container/dynamic.hpp"
#include "y/memory/io/limbo.hpp"
#include "y/core/linked/list.hpp"

namespace Yttrium
{

    namespace Core
    {
        template <typename T>
        class ListNode
        {
        public:
            Y_ARGS_DECL(T,Type);
            inline  ListNode(ParamType value) : next(0), prev(0), data(value) {}
            inline ~ListNode() noexcept {}

            inline Type &      operator*()       noexcept { return data; }
            inline ConstType & operator*() const noexcept { return data; }

            ListNode *next;
            ListNode *prev;

        private:
            Y_Disable_Copy_And_Assign(ListNode);
            MutableType data;

        };

    }

    template <typename T,typename THREADING_POLICY = SingleThreadedClass>
    class List : public DynamicContainer, public THREADING_POLICY
    {
    public:
        Y_ARGS_DECL(T,Type);
        typedef typename THREADING_POLICY::Lock             Lock;
        typedef Core::ListNode<Type>                        NodeType;
        typedef Core::ListOf<NodeType>                      ListType;
        typedef Memory::Limbo<NodeType,SingleThreadedClass> PoolType;

        inline explicit List() : list(), pool() {}

        inline virtual ~List() noexcept
        {
            release_();
        }

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



    private:
        Y_Disable_Copy_And_Assign(List);
        ListType list;
        PoolType pool;

        inline void release_() noexcept {
            while(list.size>0) pool.remove(list.popTail());
            pool.release();
        }
    };

}

#endif
