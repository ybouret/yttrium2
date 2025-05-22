
//! \file

#ifndef Y_Core_Linked_Pool_Included
#define Y_Core_Linked_Pool_Included 1

#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {
        template <typename NODE>
        class PoolOf : public Linked<NODE>
        {
        public:
            using Linked<NODE>::head;
            using Linked<NODE>::incr;
            using Linked<NODE>::decr;
            using Linked<NODE>::owns;
            using Linked<NODE>::size;

            inline explicit PoolOf() noexcept : Linked<NODE>() {}
            inline virtual ~PoolOf() noexcept
            {
                assert( (0==size && 0==head) || Die("pool memory leak") );
            }

            void store(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(!owns(node));
                assert(0==node->next);
                node->next = head;
                head       = node;
                incr();
            }

            NODE * query() noexcept
            {
                assert(0!=head);
                assert(size>0);
                NODE * const node = head;
                head = head->next;
                node->next = 0;
                decr();
            }


        private:
            Y_Disable_Copy_And_Assign(PoolOf);
        };
    }
}

#endif

