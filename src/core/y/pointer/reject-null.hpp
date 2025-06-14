
//! \file

#ifndef Y_Pointer_RejectNull_Included
#define Y_Pointer_RejectNull_Included 1

#include "y/pointer/smart.hpp"

namespace Yttrium
{
    namespace Smart
    {
        class RejectNull
        {
        public:
            explicit RejectNull(const char * const name,
                                const void * const addr) noexcept;
            virtual ~RejectNull() noexcept;
        private:
            Y_Disable_Copy_And_Assign(RejectNull);
        };


        template <typename T,
        template <typename> class Redirect>
        class RejectNullPointer : public RejectNull, public Pointer<T,Redirect>
        {
        public:
            using Pointer<T,Redirect>::pointee;
            
            explicit RejectNullPointer(const char * const uid,
                                        T * const          ptr) noexcept :
            RejectNull(uid,ptr),
            Pointer<T,Redirect>(ptr)
            {
            }

            inline virtual ~RejectNullPointer() noexcept
            {
            }

            inline friend std::ostream & operator<<(std::ostream &os, const RejectNullPointer &self)
            {
                assert(0!=pointee);
                return os << *self.pointee;
            }

        private:
            Y_Disable_Copy_And_Assign(RejectNullPointer);
        };


    }
}

#endif

