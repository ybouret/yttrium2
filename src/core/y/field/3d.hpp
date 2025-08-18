
//! \file

#ifndef Y_Field_3D_Included
#define Y_Field_3D_Included 1

#include "y/field/2d.hpp"
#include "y/field/layout/3d.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 3D Field
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In3D : public Sketch, public Format3D
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases
            typedef In1D<T> Row;    //!< alias
            typedef In2D<T> Slice;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! standalone
            /**
             \param uid name
             \param fmt format
             */
            template <typename UID>
            inline explicit In3D(const UID &      uid,
                                 const Format3D & fmt) :
            Sketch(uid,fmt->items * sizeof(T)),
            Format3D(fmt),
            sliceFormat( new Layout2D(SubLayout,**this)       ),
            rowFormat(   new Layout1D(SubLayout,*sliceFormat) ),
            slice(0),
            slices( fmt->numSlices() ),
            data( (MutableType *)wksp )
            {
                setup();
            }

            //! volume within 4D
            /**
             \param uid      name
             \param fmt      Format3D
             \param sliceFmt Format2d
             \param rowFmt   Format1D
             \param volume   memory
             */
            template <typename UID>
            inline explicit In3D(const UID &         uid,
                                 const Format3D &    fmt,
                                 const Format2D &    sliceFmt,
                                 const Format1D &    rowFmt,
                                 MutableType * const volume) :
            Sketch(uid),
            Format3D(fmt),
            sliceFormat(sliceFmt),
            rowFormat(rowFmt),
            slice(0),
            slices( fmt->numSlices() ),
            data( (MutableType *) volume )
            {
                setup();
            }

            //! cleanup
            inline virtual ~In3D() noexcept {}


            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const In3D &f)
            {
                return f.print(os,0);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! print
            /**
             \param os output stream
             \param indent indentation
             \return os
             */
            inline std::ostream & print(std::ostream &os, size_t indent) const
            {
                const Layout3D & fmt = **this;
                Core::Indent(os,indent<<1) << name << "@" << fmt << ":" << std::endl;
                ++indent;
                for(unit_t k=fmt.lower.z;k<=fmt.upper.z;++k)
                {
                    slice[k].print(os,indent);
                    if(k<fmt.upper.z) os << std::endl;
                }
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Format2D sliceFormat; //!< format for each slice
            const Format1D rowFormat;   //!< format for each row

        private:
            Y_Disable_Copy_And_Assign(In3D); //!< discardind
            Slice * const       slice;  //!< shifted slice address
            CxxSeries<Slice>    slices; //!< slices
            MutableType * const data;   //!< all items

            //! setup slices
            inline void setup()
            {
                const Layout3D &fmt = **this;
                const unit_t    klo = fmt.lower.z;
                const unit_t    kup = fmt.upper.z;
                const size_t    ips = fmt.shift.y; // items per slice
                MutableType *   ptr = data;
                for(unit_t k=klo;k<=kup;++k, ptr += ips)
                {
                    const String uid = name + Formatted::Get("[%s]", Decimal(k).c_str() );
                    slices.push(uid,sliceFormat,rowFormat,ptr);
                }
                Coerce(slice) = &slices[1] - klo;
            }
        };

    }

}

#endif

