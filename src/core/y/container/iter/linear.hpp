//! \file

#ifndef Y_Container_Iter_Linear_Included
#define Y_Container_Iter_Linear_Included 1

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
        //! Linear iterator for contiguous items
        //
        //
        //______________________________________________________________________
        template <Direction D, typename T>
        class Linear
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type);        //!< aliases
            typedef IntToType<D> WayType; //!< aliases
            static const WayType Way;     //!< type selector


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup to NULL
            inline  Linear() noexcept : pointee(0) {}

            //! cleanup
            inline ~Linear() noexcept { pointee=0; }

            //! setup with address \param addr compatible address
            inline  Linear(Type * const addr) noexcept :
            pointee( (MutableType *)addr )
            {}

            //! duplicate \param other another iterator
            inline Linear(const Linear &other) noexcept :
            pointee(other.pointee)
            {
            }

            //! assign \param other another iterator \return *this*
            inline Linear & operator=( const Linear &other ) noexcept
            {
                pointee = other.pointee;
                return *this;
            }

            //! test equality
            /**
             \param lhs first iterator
             \param rhs second iterator
             \return pointees are equal
             */
            inline friend bool operator==(const Linear &lhs, const Linear &rhs) noexcept
            {
                return lhs.pointee == rhs.pointee;
            }

            //! test difference
            /**
             \param lhs first iterator
             \param rhs second iterator
             \return pointees are different
             */
            inline friend bool operator!=(const Linear &lhs, const Linear &rhs) noexcept
            {
                return lhs.pointee != rhs.pointee;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Linear & operator++() noexcept { incr(Way); return *this; } //!< prefix increment \return *this
            inline Linear & operator--() noexcept { decr(Way); return *this; } //!< prefix decrement \return *thos

            //! post-fix increment \return copy before incremenent
            inline Linear   operator++(int) noexcept
            {
                const Linear saved = *this;
                incr(Way);
                return saved;
            }

            //! post-fix decrement \return copy before decrement
            inline Linear   operator--(int) noexcept
            {
                const Linear saved = *this;
                decr(Way);
                return saved;
            }

            //! algebra \param i initial \param n positive shift \return i+n
            friend inline Linear operator+(const Linear &i, const size_t n)
            {
                Linear j = i; assert(j.pointee==i.pointee);
                j.pointee = j.incr(n,Way);
                return j;
            }

            //! algebra \param i initial \param n negative shift \return i-n
            friend inline Linear operator-(const Linear &i, const size_t n)
            {
                Linear j = i; assert(j.pointee==i.pointee);
                j.pointee = j.decr(n,Way);
                return j;
            }



            //! access \return reference to content
            inline Type      & operator*()       noexcept { assert(0!=pointee); return *pointee; }

            //! access \return CONST reference to content
            inline ConstType & operator*() const noexcept { assert(0!=pointee); return *pointee; }


            //! \param indx shift \return *(this+indx)
            inline Type & operator[](const size_t indx) noexcept
            {
                assert(0!=pointee);
                return *incr(indx,Way);
            }

            //! \param indx shift \return *(this+indx)
            inline ConstType & operator[](const size_t indx) const noexcept
            {
                assert(0!=pointee);
                return *incr(indx,Way);
            }


        private:
            MutableType * pointee; //!< current pointe

            //! increase forward
            inline void incr(const IntToType<Forward> &) noexcept
            {
                assert(0!=pointee);
                ++pointee;
            }

            //! increase reverse
            inline void incr(const IntToType<Reverse> &) noexcept
            {
                assert(0!=pointee);
                --pointee;
            }

            //! \param n shift \return increased forward
            MutableType * incr(const size_t n, const IntToType<Forward> &) const noexcept
            {
                return (MutableType *)(pointee+n);
            }

            //! \param n shift \return increased reverse
            MutableType * incr(const size_t n, const IntToType<Reverse> &) const noexcept
            {
                return (MutableType *)(pointee-n);
            }



            //! decrease forward
            inline void decr(const IntToType<Forward> &) noexcept
            {
                assert(0!=pointee);
                --pointee;
            }

            //! decrease reverse
            inline void decr(const IntToType<Reverse> &) noexcept
            {
                assert(0!=pointee);
                ++pointee;
            }

        };

        template <Direction D, typename T>
        const typename Linear<D,T>::WayType Linear<D,T>::Way = {};


    }

}

#endif

