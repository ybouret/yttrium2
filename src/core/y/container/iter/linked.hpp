

#ifndef Y_Container_Iter_Linked_Included
#define Y_Container_Iter_Linked_Included 1

#include "y/container/iter.hpp"
#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Iter
    {
        //______________________________________________________________________
        //
        //
        //
        //! Linked iterator
        //
        //
        //______________________________________________________________________
        template <Direction D, typename NODE>
        class Linked
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef IntToType<D> WayType;                          //!< aliases
            static const WayType Way;                              //!< type selector
            Y_ARGS_EXPOSE(NODE,NodeType);                          //!< aliases
            Y_ARGS_EXPOSE(typename NODE::Type,Type);               //!< aliases
            static const bool IsConst = TypeTraits<NODE>::IsConst; //!< type selector
            typedef typename Pick<IsConst,ConstType,Type>::Type ResultType;      //!< for normal access
            typedef ConstType                                   ConstResultType; //!< for const access


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param userNode a doubly linked node
            inline Linked(NODE * const userNode) noexcept :
            node( (MutableNodeType *) userNode )
            {
            }

            //! cleanup
            inline ~Linked() noexcept { node=0; }

            //! copy \param other another iterator
            inline  Linked(const Linked &other) noexcept : node(other.node) {}

            //! assign \param other another iterator \return *this*
            inline  Linked & operator=(const Linked &other) noexcept
            {
                node = other.node;
                return *this;
            }

            //! normal access \return content
            inline ResultType & operator*()       noexcept { assert(0!=node); return **node; }

            //! const access \return const content
            inline ConstType  & operator*() const noexcept { assert(0!=node); return **node; }

            //! test equality
            /**
             \param lhs first iterator
             \param rhs second iterator
             \return pointees are equal
             */
            inline friend bool operator==(const Linked &lhs, const Linked &rhs) noexcept
            {
                return lhs.node == rhs.node;
            }

            //! test difference
            /**
             \param lhs first iterator
             \param rhs second iterator
             \return pointees are different
             */
            inline friend bool operator!=(const Linked &lhs, const Linked &rhs) noexcept
            {
                return lhs.node != rhs.node;
            }

            inline Linked & operator++() noexcept { incr(Way); return *this; } //!< prefix increment \return *this
            inline Linked & operator--() noexcept { decr(Way); return *this; } //!< prefix decrement \return *thos

            //! post-fix increment \return copy before incremenent
            inline Linked   operator++(int) noexcept
            {
                const Linked saved = *this;
                incr(Way);
                return saved;
            }

            //! post-fix decrement \return copy before decrement
            inline Linked   operator--(int) noexcept
            {
                const Linked saved = *this;
                decr(Way);
                return saved;
            }


        private:
            MutableNodeType *node; //!< internal node

            //! increase forward
            inline void incr(const IntToType<Forward> &) noexcept
            {
                assert(0!=node);
                node=node->next;
            }

            //! increase reverse
            inline void incr(const IntToType<Reverse> &) noexcept
            {
                assert(0!=node);
                node=node->prev;
            }

            //! decrease forward
            inline void decr(const IntToType<Forward> &) noexcept
            {
                assert(0!=node);
                node=node->prev;
            }

            //! decrease reverse
            inline void decr(const IntToType<Reverse> &) noexcept
            {
                assert(0!=node);
                node=node->next;
            }
        };

        template <Direction D, typename NODE>
        const typename Linked<D,NODE>::WayType Linked<D,NODE>::Way = {};


    }

}

#endif

