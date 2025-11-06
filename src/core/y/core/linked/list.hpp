

//! \file

#ifndef Y_Core_Linked_List_Included
#define Y_Core_Linked_List_Included 1

#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! basic list operations
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class ListOf : public Linked<NODE>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            using Linked<NODE>::head;
            using Linked<NODE>::incr;
            using Linked<NODE>::decr;
            using Linked<NODE>::owns;
            using Linked<NODE>::size;
            using Linked<NODE>::warning;
            using Linked<NODE>::CompareAddresses;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty
            inline explicit ListOf() noexcept : Linked<NODE>(), tail(0) {}

            //! cleanup, should be empty
            inline virtual ~ListOf() noexcept
            {
                assert( (0==size && 0==head && 0==tail) || Die("list memory leak") );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check standalone valid node
            /**! \param node any node \return sanity of node **/
            inline bool isValid(const NODE * const node) const noexcept
            {
                if(0==node)       return warning(LinkedInfo::NullNode);
                if(0!=node->next) return warning(LinkedInfo::UsedNext);
                if(0!=node->prev) return warning(LinkedInfo::UsedNext);
                if(owns(node))    return warning(LinkedInfo::OwnsNode);
                return true;
            }

            //! push new node at tail of list
            /** \param node a valid node \return node */
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

            //! push new node at head of list
            /** \param node a valid node \return node */
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

            //! remove tail node
            /** \return unlinked tail */
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

            //! remove head node
            /** \return unlinked head */
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

            //! remove any node
            /** \param node a node of the list \return unlinked node */
            inline NODE * pop(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(owns(node));
                if(head==node) return popHead();
                if(tail==node) return popTail();
                assert(size>=3);
                NODE * const next = node->next; assert(0!=next);
                NODE * const prev = node->prev; assert(0!=prev);
                prev->next = next;
                next->prev = prev;
                node->prev = 0 ;
                node->next = 0;
                decr();
                assert(isValid(node));
                return node;
            }

            //! no-throw swap list content
            /** \param other another list */
            inline void swapListFor(ListOf &other) noexcept
            {
                this->swapLinkedFor(other);
                CoerceSwap(tail,other.tail);
            }

            //! split list into two halves
            /**
             \param lhs accepts first part
             \param rhs accepts second part
             */
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

            //! wrapper to compare data
            template <typename COMPARE_DATA>
            struct CompareDataThruNodes
            {
                COMPARE_DATA &proc; //!< compare node data

                //! comparison call
                /**
                 \param lhs lhs node
                 \param rhs rhs node
                 \return proc(**lhs,**rhs)
                 */
                inline SignType operator()(const NODE * const lhs,
                                           const NODE * const rhs) noexcept
                {
                    return proc(**lhs,**rhs);
                }
            };

            //! fusion of two sorted list
            /**
             \param lhs first sorted list
             \param rhs second sorted list
             \param compareNodes comparison function
             */
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

            //! fusion with data comparison
            /**
             \param lhs first sorted list
             \param rhs second sorted list
             \param proc data comparison function
            */
            template <typename LIST, typename COMPARE_DATA> inline
            void fusionWith(COMPARE_DATA &proc, LIST &lhs, LIST &rhs) noexcept
            {
                CompareDataThruNodes<COMPARE_DATA> compareNodes = { proc };
                fusion(lhs,rhs,compareNodes);
            }


            //! recursive merge sort
            /**
             \param compareNodes comparison function
             */
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

            //! recursive merge sort
            /**
             \param proc data comparison function
             */
            template <typename COMPARE_DATA> inline
            void sortWith(COMPARE_DATA &proc) noexcept
            {
                CompareDataThruNodes<COMPARE_DATA> compareNodes = { proc };
                sort(compareNodes);
            }

            //! merging a list to tail
            /**
             \param other list to be merged, emptied
             \return self+other
             */
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

            //! merge at head
            /**
             \param other another list
             \return *this = other + *this
             */
            template <typename LIST>
            inline ListOf & mergeHead(LIST &other) noexcept
            {
                other.mergeTail(*this);
                swapListFor(other);
                return *this;
            }


            //! insertion after a given node
            /**
             \param mine one of my node
             \param node a valid node
             \return node inserted after mine
             */
            inline NODE * insertAfter(NODE * const mine, NODE * const node) noexcept
            {
                assert(0!=mine); assert(owns(mine));
                assert(0!=node); assert(isValid(node));
                if(mine==tail) return pushTail(node);

                assert(size>1);
                NODE * const next = node->next = mine->next;
                NODE * const prev = node->prev = next->prev;
                next->prev = prev->next = node;
                incr();
                return node;
            }
            

            //! insertion before a given node
            /**
             \param mine one of my node
             \param node a valid node
             \return node inserted before mine
             */
            inline NODE * insertBefore(NODE * const mine, NODE * const node) noexcept
            {
                assert(0!=mine); assert(owns(mine));
                assert(0!=node); assert(isValid(node));
                if(mine==head) return pushHead(node);

                assert(size>1);
                NODE * const prev = node->prev = mine->prev;
                NODE * const next = node->next = prev->next;
                prev->next = next->prev = node;
                incr();
                return node;
            }


            //! move one of my node towards head
            /**
             \param node one of my node
             \return node moved towards head if possible
             */
            inline NODE * towardsHead(NODE * const node) noexcept
            {
                assert(0!=node);
                assert(owns(node));
                NODE * const prev = node->prev;
                if(0!=prev) insertBefore(prev,pop(node));
                return node;
            }


            //! insertion in a previously ordered list
            /**
             \param compareNodes node comparison
             \param node a valid node
             \return node inserted at its right position
             */
            template <typename COMPARE_NODES> inline
            NODE * insertOrderedBy(COMPARE_NODES &compareNodes, NODE * const node) noexcept
            {
                assert(this->isOrderedBy(compareNodes,Sign::LooselyIncreasing));
                assert(isValid(node));

                switch(size)
                {
                    case 1:
                        switch( compareNodes(node,head) )
                        {
                            case Negative:
                            case __Zero__: return pushHead(node);
                            case Positive:
                                break;
                        }
                        // FALLTHRU
                    case 0:
                        return pushTail(node);
                    default:
                        break;
                }

                assert(size>=2);
                assert(head!=tail);
                assert(0!=head);
                assert(0!=tail);
                NODE * lower = head;
                switch( compareNodes(node,lower) )
                {
                    case Negative:
                    case __Zero__:
                        return pushHead(node);
                    case Positive:
                        break;
                }

                NODE * const upper = tail;
                switch( compareNodes(node,upper) )
                {
                    case Positive:
                    case __Zero__:
                        return pushTail(node);
                    case Negative:
                        break;
                }

            PROBE:
                {
                    NODE * const probe = lower->next; assert(0!=probe);
                    if(upper==probe)
                        goto INSERT_AFTER_LOWER;

                    switch( compareNodes(node,probe) )
                    {
                        case Negative:
                        case __Zero__: goto INSERT_AFTER_LOWER;
                        case Positive: lower=probe; goto PROBE;
                    }
                }

            INSERT_AFTER_LOWER:
                return insertAfter(lower,node);
            }


            //! insertion in a previously ordered list
            /**
             \param proc data comparison
             \param node a valid node
             \return node inserted at its right position
             */
            template <typename COMPARE_DATA> inline
            NODE * insertOrderedWith(COMPARE_DATA &proc, NODE * const node) noexcept
            {
                CompareDataThruNodes<COMPARE_DATA> compareNodes = { proc };
                return insertOrderedBy(compareNodes,node);
            }


            //! insert using address comparison
            /**
             \param node a valid node
             \return node inserted by increasing address
             */
            inline NODE * insertOderedByAddresses(NODE * const node) noexcept
            {
                return insertOrderedBy(CompareAddresses,node);
            }

            //! sort by increasing address of nodes
            inline void sortByIncreasingAddress() noexcept
            {
                sort( CompareAddresses );
            }


            //! move to front
            /**
             \param node selected node of list
             \return node
             */
            NODE * moveToFront(NODE * const node) noexcept
            {
                assert(0!=node);
                assert( owns(node) );
                if(node!=head)
                    return pushHead( pop(node) );
                return node;
            }

            //! \param nodeIndex valid index>0 \return node at index
            inline NODE * fetch(const size_t nodeIndex) noexcept
            {
                return (NODE *) doFetch(nodeIndex);
            }

            //! \param nodeIndex valid index>0 \return node at index
            inline const NODE * fetch(const size_t nodeIndex) const noexcept
            {
                return (NODE *) doFetch(nodeIndex);
            }


            //! reverse order
            inline void reverse() noexcept
            {
                ListOf tmp;
                while(size>0) tmp.pushTail( popTail() );
                swapListFor(tmp);
            }

            //! pushTail( popHead() ) \return *this
            inline ListOf & moveHeadToTail() noexcept
            {
                if(size>=2) (void) pushTail( popHead() );
                return *this;
            }

            //! pushHead( popTail() ) \return *this
            inline ListOf & moveTailToHead() noexcept
            {
                if(size>=2) (void) pushHead( popTail() );
                return *this;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            NODE *tail; //!< tail (sentinel) node

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

#endif // !Y_Core_Linked_List_Included

