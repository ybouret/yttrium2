

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
                if(0==node)       return warning(LinkedInfo::NullNode);
                if(0!=node->next) return warning(LinkedInfo::UsedNext);
                if(0!=node->prev) return warning(LinkedInfo::UsedNext);
                if(owns(node))    return warning(LinkedInfo::OwnsNode);
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

            template <typename LIST>inline
            void split(LIST &lhs, LIST &rhs) noexcept
            {
                assert(0==lhs.size);
                assert(0==rhs.size);
#if !defined(NDEBUG)
                const size_t oldSize = size;
#endif
                // send to lhs
                {
                    const size_t half = size>>1;
                    while(size>half) lhs.pushTail( popHead() );
                }

                // send to rhs
                swapListFor(rhs);
                assert(0==size);
                assert(lhs.size+rhs.size==oldSize);
            }

            template <typename LIST, typename COMPARE_NODES> inline
            void fusion(LIST &lhs, LIST &rhs, COMPARE_NODES &compareNodes) noexcept
            {
                assert(0==size);
                assert(lhs.isOrderedBy(compareNodes,Sign::LooselyIncreasing));
                assert(rhs.isOrderedBy(compareNodes,Sign::LooselyIncreasing));
#if !defined(NDEBUG)
                const size_t oldSize = lhs.size+rhs.size;
#endif
                while(lhs.size>0 && rhs.size>0)
                {
                    switch( compareNodes(lhs.head,rhs.head) )
                    {
                        case Negative:
                        case __Zero__: pushTail( lhs.popHead() ); continue;
                        case Positive: pushTail( rhs.popHead() ); continue;
                    }
                }
                mergeTail(lhs);
                mergeTail(rhs);
                assert(oldSize==size);
                assert(this->isOrderedBy(compareNodes,Sign::LooselyIncreasing));
            }

            template <typename COMPARE_NODES> inline
            void sort(COMPARE_NODES &compareNodes) noexcept
            {
                if(size>1) {
                    ListOf lhs, rhs;
                    split(lhs,rhs);
                    lhs.sort(compareNodes);
                    rhs.sort(compareNodes);
                    fusion(lhs,rhs,compareNodes);
                }
            }

            template <typename LIST>
            inline ListOf & mergeTail(LIST &other) noexcept
            {
                switch(size)
                {
                    case 0:
                        swapListFor(other);
                        break;

                    case 1:
                        other.pushHead( popTail() );
                        swapListFor(other);
                        break;

                    default:
                        switch(other.size)
                        {
                            case 0:
                                break;

                            case 1:
                                pushTail( other.popHead() );
                                break;

                            default:
                                tail->next = other.head;
                                other.head->prev = tail;
                                tail = other.tail;
                                Coerce(size) += other.size;
                                Coerce(other.size) = 0;
                                Coerce(other.head) = 0;
                                Coerce(other.tail) = 0;
                                break;
                        }
                        break;
                }

                assert(0==other.size);
                return *this;
            }


            NODE *tail;

        private:
            Y_Disable_Copy_And_Assign(ListOf); //!< discarding

            inline virtual const NODE * doFetch(size_t nodeIndex) const noexcept
            {
                assert(nodeIndex>=1);
                assert(nodeIndex<=size);
                const size_t half = size >> 1;
                if(nodeIndex<=half)
                {
                    const NODE *node = head; assert(0!=node);
                    while(--nodeIndex>0) {
                        assert(0!=node);
                        node = node->next;
                    }
                    assert(0!=node);
                    return node;
                }
                else
                {
                    const NODE *node = tail; assert(0!=node);
                    nodeIndex = size-nodeIndex;
                    while(nodeIndex-- > 0) {
                        assert(0!=node);
                        node = node->prev;
                    }
                    assert(0!=node);
                    return node;
                }
            }
        };
    }
}

#endif

