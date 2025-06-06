//! \file

#ifndef Y_Core_Linked_Included
#define Y_Core_Linked_Included 1

#include "y/core/setup.hpp"
#include "y/check/usual.hpp"
#include "y/type/sign.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Core
    {

        //______________________________________________________________________
        //
        //
        //! common data for Linked structures
        //
        //______________________________________________________________________
        struct LinkedInfo
        {
            static const char OwnsNode[]; //!< "owns node!"
            static const char NullNode[]; //!< "NULL==node"
            static const char UsedNext[]; //!< "NULL!=next"
            static const char UsedPrev[]; //!< "NULL!=prev"
        };

        //______________________________________________________________________
        //
        //
        //
        //! base class and methods for Linked structures
        //
        //
        //______________________________________________________________________
        template <typename NODE>
        class Linked
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef NODE NodeType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Linked() noexcept : size(0), head(0) {} //!< initialize
            inline virtual ~Linked() noexcept {}                    //!< cleanup



            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! check ownership
            /** \param node any node \return true if linked to this */
            inline bool owns(const NODE * const node) const noexcept
            {
                for(const NODE *mine=head;mine;mine=mine->next)
                {
                    if( node == mine ) return true;
                }
                return false;
            }

            //! get const NODE in [1..size]
            /**
             \param indx valid index
             \return indx-th node
             */
            inline const NODE * operator[](const size_t indx) const noexcept
            {
                return doFetch(indx);
            }

            //! get NODE in [1..size]
            /**
             \param indx valid index
             \return indx-th node
             */
            inline NODE * operator[](const size_t indx) noexcept
            {
                return (NODE *)doFetch(indx);
            }


            //! display assuming NODE has an operator*()
            /**
             \param os output stream
             \param self this
             \return os
             */
            inline friend std::ostream & operator<<( std::ostream &os, const Linked &self)
            {
                os << '[';
                const NODE *node = self.head;
                if(node)
                {
                    os << **node;
                    for(node=node->next;node;node=node->next)
                        os << ';' << **node;
                }
                os << ']';
                return os;
            }

            //! helper to debug
            /** \param msg message to print \return false */
            bool warning(const char * const msg) const noexcept {
                try { std::cerr << msg << std::endl; }
                catch(...) {}
                return false;
            }


            //! check orderer linked structure
            /**
             \param compareNodes nodes comparator
             \param qualifies    sign qualification
             \return true if all succesive nodes qualifiy
             */
            template <typename COMPARE_NODES, typename QUALIFIES> inline
            bool isOrderedBy(COMPARE_NODES & compareNodes,
                             QUALIFIES &     qualifies) const
            {
                if(0!=head)
                {
                    for(const NODE *curr=head;curr->next;curr=curr->next)
                    {
                        const SignType comparison = compareNodes(curr,curr->next);
                        if( !qualifies(comparison) ) return false;
                    }
                }
                return true;
            }

            //! compare nodes by address
            /**
             \param lhs first node
             \param rhs second node
             \return address order
             */
            static inline SignType CompareAddresses(const NODE * const lhs,
                                                    const NODE * const rhs) noexcept
            {
                return Sign::Of(lhs,rhs);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t size; //!< current size
            NODE *       head; //!< current head

        protected:
            //! increase size
            inline void incr() noexcept { ++Coerce(size); }

            //! decrease size
            inline void decr() noexcept {
                assert(size>0 || Die("empty Linked") );
                --Coerce(size);
                assert(!(0==size&&0!=head) || Die("empty Linked with head!=NULL"));
            }

            //! C-swap size and head
            /** \param other other linked */
            inline void swapLinkedFor(Linked &other) noexcept
            {
                CoerceSwap(size,other.size);
                CoerceSwap(head,other.head);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! getch node in [1..size]
            /**
             \param nodeIndex valid index
             \return NODE address
             */
            virtual const NODE * doFetch(size_t nodeIndex) const noexcept =0;

        private:
            Y_Disable_Copy_And_Assign(Linked); //!< discarding
        };
    }
}

#endif

