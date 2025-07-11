//! \file

#ifndef Y_Pointer_Smart_Included
#define Y_Pointer_Smart_Included 1

#include "y/pointer/immediate.hpp"
#include <cassert>
#include <iostream>

namespace Yttrium
{
    namespace Smart
    {
        //______________________________________________________________________
        //
        //
        //
        //! base class for SmartPointer
        //
        //
        //______________________________________________________________________
        template <
        typename T,
        template <typename> class Redirect = Immediate
        >
        class Pointer : public Redirect<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return content
            inline Type      & operator*()       noexcept { assert(0!=pointee); return *pointee; }

            //! \return const content
            inline ConstType & operator*() const noexcept { assert(0!=pointee); return *pointee; }

            //! \return result of Redirect
            inline typename Redirect<T>::ReturnType      operator->() noexcept       { assert(pointee); return this->fetch(pointee); }

            //! \return const result of Redirect
            inline typename Redirect<T>::ConstReturnType operator->() const noexcept { assert(pointee); return this->fetch(pointee); }


            //! content exchange \param other another pointer
            inline void xch(Pointer &other) noexcept
            {
                Swap(pointee,other.pointee);
            }
            
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param ptr an acceptable address
            inline explicit Pointer(T * const ptr) : Redirect<T>(), pointee( (MutableType*) ptr) {}

            //! cleanup, pointee should be NULL
            inline virtual ~Pointer() noexcept { assert(0==pointee); }



            MutableType * pointee; //!< the pointee

        private:
            Y_Disable_Copy_And_Assign(Pointer); //!< discarding
        };

        

    }
}

#endif


