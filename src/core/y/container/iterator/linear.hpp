//! \file

#ifndef Y_Container_Iterator_Linear_Included
#define Y_Container_Iterator_Linear_Included 1

#include "y/container/iterator.hpp"
#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Iterator
    {

        template <Direction D, typename T>
        class Linear
        {
        public:
            Y_ARGS_EXPOSE(T,Type);
            typedef IntToType<D> WayType;
            static const WayType Way;

            inline  Linear() noexcept : pointee(0) {}

            inline ~Linear() noexcept { pointee=0; }

            inline  Linear(Type * const addr) noexcept :
            pointee( (MutableType *)addr )
            {}

            inline Linear(const Linear &other) noexcept :
            pointee(other.pointee)
            {
            }
            
            inline Linear & operator=( const Linear &other ) noexcept
            {
                pointee = other.pointee;
                return *this;
            }

            inline friend bool operator==(const Linear &lhs, const Linear &rhs) noexcept
            {
                return lhs.pointee == rhs.pointee;
            }

            inline friend bool operator!=(const Linear &lhs, const Linear &rhs) noexcept
            {
                return lhs.pointee != rhs.pointee;
            }


            inline Linear & operator++() noexcept { incr(Way); return *this; }
            inline Linear & operator--() noexcept { decr(Way); return *this; }
            inline Linear   operator++(int) noexcept
            {
                const Linear saved = *this;
                incr(Way);
                return saved;
            }

            inline Linear   operator--(int) noexcept
            {
                const Linear saved = *this;
                decr(Way);
                return saved;
            }

            inline Type      & operator*()       noexcept { assert(0!=pointee); return *pointee; }
            inline ConstType & operator*() const noexcept { assert(0!=pointee); return *pointee; }

            


        private:
            MutableType * pointee;

            inline void incr(const IntToType<Forward> &) noexcept
            {
                assert(0!=pointee);
                ++pointee;
            }

            inline void incr(const IntToType<Reverse> &) noexcept
            {
                assert(0!=pointee);
                --pointee;
            }

        };

        template <Direction D, typename T>
        const typename Linear<D,T>::WayType Linear<D,T>::Way = {};


    }

}

#endif

