//! \file

#ifndef Y_Field_1D_Included
#define Y_Field_1D_Included 1

#include "y/field/sketch.hpp"
#include "y/field/layout/1d.hpp"
#include "y/memory/operating.hpp"
#include "y/container/light-array.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 1D Field
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In1D : public Sketch, public Format1D
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! standalone field
            /**
             \param uid name
             \param fmt format
             */
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

            //! cleanup
            inline virtual ~In1D() noexcept
            {
                Coerce(obj) += (*this)->lower;
            }

            //! sub field
            /**
             \param uid name
             \param fmt format
             \param ptr data pointer
             */
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

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const In1D &f)
            {
                return f.print(os,0);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            inline std::ostream & print(std::ostream &os, size_t indent) const
            {
                const Layout1D &    fmt = **this;
                const LightArray<T> arr(obj+fmt.lower,fmt.width);
                return Core::Indent(os,indent<<1) << name << "@" << fmt << ": " << arr;
            }

            //! \param i data index \return (*this)[i]
            inline Type & operator[](const unit_t i) noexcept
            {
                assert(i>=(*this)->lower);
                assert(i<=(*this)->upper);
                return obj[i];
            }

            //! \param i data index \return (*this)[i]
            inline ConstType & operator[](const unit_t i) const noexcept
            {
                assert(i>=(*this)->lower);
                assert(i<=(*this)->upper);
                return obj[i];
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Y_Disable_Copy_And_Assign(In1D); //!< discarding
            T * const            obj;        //!< memory location
            Memory::Operating<T> ops;        //!< objects I/O
        };

    }

}

#endif

