
//! \file

#ifndef Y_Pointer_RejectNull_Included
#define Y_Pointer_RejectNull_Included 1

#include "y/pointer/smart.hpp"

namespace Yttrium
{
    namespace Smart
    {
        //______________________________________________________________________
        //
        //
        //
        //! common class for RejectNullPointer
        //
        //
        //______________________________________________________________________
        class RejectNull
        {
        public:
            
            //! critical setup \param name class id \param addr address to check
            explicit RejectNull(const char * const name,
                                const void * const addr) noexcept;
            //! cleanup
            virtual ~RejectNull() noexcept;
        private:
            Y_Disable_Copy_And_Assign(RejectNull); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! Base class for Pointer with forbidden NULL
        //
        //
        //______________________________________________________________________
        template <typename T,
        template <typename> class Redirect>
        class RejectNullPointer : public RejectNull, public Pointer<T,Redirect>
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
             \param uid class id
             \param ptr object, NULL => critical error
             */
            explicit RejectNullPointer(const char * const uid,
                                        T * const          ptr) noexcept :
            RejectNull(uid,ptr),
            Pointer<T,Redirect>(ptr)
            {
            }

            //! cleanup
            inline virtual ~RejectNullPointer() noexcept
            {
            }

            //!  forward display
            /**
             \param os output stream
             \param self *this
             \return os << **self
             */
            inline friend std::ostream & operator<<(std::ostream &os, const RejectNullPointer &self)
            {
                assert(0!=self.pointee);
                return os << *self.pointee;
            }

        private:
            Y_Disable_Copy_And_Assign(RejectNullPointer); //!< discarding
        };


    }
}

#endif

