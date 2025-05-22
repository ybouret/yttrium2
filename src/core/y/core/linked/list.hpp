

//! \file

#ifndef Y_Core_Linked_List_Included
#define Y_Core_Linked_List_Included 1

#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {
        template <typename NODE>
        class ListOf : public Linked<NODE>
        {
        public:
            using Linked<NODE>::head;
            using Linked<NODE>::incr;
            using Linked<NODE>::decr;
            using Linked<NODE>::owns;
            using Linked<NODE>::size;

            inline explicit ListOf() noexcept : Linked<NODE>(), tail(0) {}
            inline virtual ~ListOf() noexcept
            {
                assert( (0==size && 0==head && 0==tail) || Die("list memory leak") );
            }

            NODE *tail;

            inline NODE * pushTail(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(!owns(node));
                assert(0==node->next);
                assert(0==node->prev);
                if( size <= 0 )
                    head = tail = node;
                else
                {
                    node->prev = tail;
                    tail->next = node;
                    tail       = node;
                }
                incr();
                return node;
            }


        private:
            Y_Disable_Copy_And_Assign(ListOf);
        };
    }
}

#endif

