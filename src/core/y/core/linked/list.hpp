

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
            using Linked<NODE>::warning;

            inline explicit ListOf() noexcept : Linked<NODE>(), tail(0) {}
            inline virtual ~ListOf() noexcept
            {
                assert( (0==size && 0==head && 0==tail) || Die("list memory leak") );
            }

            inline bool isValid(const NODE * const node) const noexcept
            {
                if(0==node)       return warning(LinkedInfo::NullNodeMsg);
                if(0!=node->next) return warning(LinkedInfo::UsedNextMsg);
                if(0!=node->prev) return warning(LinkedInfo::UsedNextMsg);
                if(owns(node))    return warning(LinkedInfo::OwnsNodeMsg);
                return true;
            }

            inline NODE * pushTail(NODE * const node) noexcept
            {
                assert( isValid(node) );
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

            inline NODE * pushHead(NODE * const node) noexcept
            {
                assert( isValid(node) );
                if( size <= 0 )
                    head = tail = node;
                else
                {
                    node->next = head;
                    head->prev = node;
                    head       = node;
                }
                incr();
                return node;
            }

            inline NODE * popTail() noexcept
            {
                assert(size>0);
                assert(0!=tail);
                NODE * const node = tail;
                if(size<=1)
                {
                    assert(1==size);
                    tail = head = 0;
                }
                else
                {
                    tail = tail->prev;
                    tail->next = 0;
                    node->prev = 0;
                }
                decr();
                assert(isValid(node));
                return node;
            }

            inline NODE * popHead() noexcept
            {
                assert(size>0);
                assert(0!=head);
                NODE * const node = head;
                if(size<=1)
                {
                    assert(1==size);
                    tail = head = 0;
                }
                else
                {
                    head = head->next;
                    head->prev = 0;
                    node->next = 0;
                }
                decr();
                assert(isValid(node));
                return node;
            }

            inline void swapListFor(ListOf &other) noexcept
            {
                this->swapLinkedFor(other);
                CoerceSwap(tail,other.tail);
            }


            NODE *tail;



        private:
            Y_Disable_Copy_And_Assign(ListOf);
        };
    }
}

#endif

