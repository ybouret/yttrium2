
//! \file

#ifndef Y_Pointer_AccepttNull_Included
#define Y_Pointer_AccepttNull_Included 1

#include "y/pointer/smart.hpp"

namespace Yttrium
{
    namespace Smart
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base class for Pointer with allowrd NULL
        //
        //
        //______________________________________________________________________
        template <typename T,
        template <typename> class Redirect>
        class AcceptNullPointer : public Pointer<T,Redirect>
        {
        public:
            using Pointer<T,Redirect>::pointee;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param ptr any object address
             */
            explicit AcceptNullPointer(T * const ptr) noexcept :
            Pointer<T,Redirect>(ptr)
            {
            }

            //! cleanup
            inline virtual ~AcceptNullPointer() noexcept
            {
            }

            //!  forward display
            /**
             \param os output stream
             \param self *this
             \return os
             */
            inline friend std::ostream & operator<<(std::ostream &os, const AcceptNullPointer &self)
            {
                if(self.pointee) return os << *self.pointee;
                else             return os << Core::Nil;
            }


            inline bool isEmpty() const noexcept { return 0 == pointee; } //!< \return 0 == pointee
            inline bool isValid() const noexcept { return 0 != pointee; } //!< \return 0 != pointee

        private:
            Y_Disable_Copy_And_Assign(AcceptNullPointer); //!< discarding
        };
    }

}

#endif
