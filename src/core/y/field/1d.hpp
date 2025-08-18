//! \file

#ifndef Y_Field_1D_Included
#define Y_Field_1D_Included 1

#include "y/field/sketch.hpp"
#include "y/field/layout/1d.hpp"
#include "y/memory/operating.hpp"

namespace Yttrium
{

    namespace Field
    {

        template <typename T>
        class In1D : public Sketch, public Format1D
        {
        public:
            Y_Args_Declare(T,Type);

            template <typename UID>
            inline explicit In1D(const UID &      uid,
                                 const Format1D & fmt) :
            Sketch(uid,fmt->items*sizeof(T)),
            Format1D(fmt),
            obj( static_cast<MutableType *>(wksp) ),
            ops( obj, fmt->items )
            {
                Coerce(obj) -= (*this)->lower;
            }

            inline virtual ~In1D() noexcept
            {
                Coerce(obj) += (*this)->lower;
            }

            template <typename UID>
            inline explicit In1D(const UID &      uid,
                                 const Format1D & fmt,
                                 T * const        ptr) :
            Sketch(uid),
            Format1D(fmt),
            obj( ptr ),
            ops( obj, fmt->items )
            {
                Coerce(obj) -= (*this)->lower;
            }

            inline friend std::ostream & operator<<(std::ostream &os, const In1D &f)
            {
                const Layout1D &fmt = *f;
                os << f.name << "=" << fmt;
                return os;
            }

            inline Type & operator[](const unit_t i) noexcept
            {
                assert(i>=(*this)->lower);
                assert(i<=(*this)->upper);
                return obj[i];
            }

            inline ConstType & operator[](const unit_t i) const noexcept
            {
                assert(i>=(*this)->lower);
                assert(i<=(*this)->upper);
                return obj[i];
            }

        private:
            Y_Disable_Copy_And_Assign(In1D);
            T * const            obj;
            Memory::Operating<T> ops;
        };

    }

}

#endif

