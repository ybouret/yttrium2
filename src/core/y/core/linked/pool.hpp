
//! \file

#ifndef Y_Core_Linked_Pool_Included
#define Y_Core_Linked_Pool_Included 1

#include "y/core/linked.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! basic Pool of NODEs
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class PoolOf : public Linked<NODE>
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

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize
            inline explicit PoolOf() noexcept : Linked<NODE>() {}

            //! cleanup
            inline virtual ~PoolOf() noexcept
            {
                assert( (0==size && 0==head) || Die("pool memory leak") );
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check NODE validity : unlinked not null
            /**
             an error message is printed if a test fails
             \param node any node
             \return true iff all tests succeed
             */
            inline bool isValid(const NODE * const node) const noexcept
            {
                if(0==node)       return warning(LinkedInfo::NullNode);
                if(0!=node->next) return warning(LinkedInfo::UsedNext);
                if(owns(node))    return warning(LinkedInfo::OwnsNode);
                return true;
            }


            //! store a node at head
            /**
             \param node a valid node
             \return stored node
             */
            inline NODE * store(NODE * const node) noexcept
            {
                assert( isValid(node) );
                node->next = head;
                head       = node;
                incr();
                return node;
            }

            //! query first node that must exists
            /** \return unlinked head */
            inline NODE * query() noexcept
            {
                assert(0!=head);
                assert(size>0);
                NODE * const node = head;
                head = head->next;
                node->next = 0;
                decr();
                assert(isValid(node));
                return node;
            }

            //! store a node at end (SLOWER)
            /**
             \param node a valid node
             \return store node at end of pool
             */
            inline NODE * stash(NODE * const node) noexcept
            {
                assert( isValid(node) );
                if(0==head)
                {
                    assert(0==size);
                    return store(node);
                }
                else
                {
                    NODE * tail = head;
                    while(0!=tail->next)
                        tail=tail->next;
                    assert(0==tail->next);
                    incr();
                    return (tail->next = node);
                }
            }

            //! swap pool members
            /**
             \param other another pool
             */
            inline void swapPoolFor(PoolOf &other) noexcept
            {
                this->swapLinkedFor(other);
            }

            template <typename POOL>
            inline void split(POOL &lhs, POOL &rhs) noexcept
            {
                assert(0==lhs.size);
                assert(0==rhs.size);
#if !defined(NDEBUG)
                const size_t oldSize = size;
#endif
                // send to lhs
                {
                    const size_t half = size>>1;
                    while(size>half) lhs.store( query() );
                }

                // send to rhs
                swapPoolFor(rhs);
                assert(0==size);
                assert(lhs.size+rhs.size==oldSize);
            }



        private:
            Y_Disable_Copy_And_Assign(PoolOf); //!< discarding

            inline virtual const NODE * doFetch(size_t nodeIndex) const noexcept
            {
                assert(nodeIndex>=1);
                assert(nodeIndex<=size);
                const NODE *node = head; assert(0!=node);
                while(--nodeIndex>0) {
                    assert(0!=node);
                    node = node->next;
                }
                assert(0!=node);
                return node;
            }

        };
    }
}

#endif

