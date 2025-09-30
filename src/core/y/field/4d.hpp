
//! \file

#ifndef Y_Field_4D_Included
#define Y_Field_4D_Included 1

#include "y/field/3d.hpp"
#include "y/field/layout/4d.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 4D Field
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In4D : public Sketch, public Format4D
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
            typedef In3D<T> Volume;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning ( disable : 4355 )
#endif

            //! standalone
            /**
             \param uid name
             \param fmt format
             */
            template <typename UID>
            inline explicit In4D(const UID &      uid,
                                 const Format4D & fmt) :
            Sketch(uid,fmt->items * sizeof(T)),
            Format4D(fmt),
            volumeFormat( new Layout3D(SubLayout,**this)        ),
            sliceFormat(  new Layout2D(SubLayout,*volumeFormat) ),
            rowFormat(    new Layout1D(SubLayout,*sliceFormat)  ),
            volume(0),
            volumes( fmt->numVolumes() ),
            data( (MutableType *) wksp )
            {
                setup();
            }

#if defined(_MSC_VER)
#pragma warning (pop)
#endif

            //! cleanup
            inline virtual ~In4D() noexcept {}


            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const In4D &f)
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
                const Layout4D & fmt = **this;
                Core::Indent(os,indent<<1) << name << "@" << fmt << ":" << std::endl;
                ++indent;
                for(unit_t l=fmt.lower.w;l<=fmt.upper.w;++l)
                {
                    volume[l].print(os,indent);
                    if(l<fmt.upper.w) os << std::endl;
                }
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Format3D volumeFormat; //!< format for each volume
            const Format2D sliceFormat;  //!< format for each slice
            const Format1D rowFormat;    //!< format for each row

        private:
            Y_Disable_Copy_And_Assign(In4D); //!< discardind
            Volume * const      volume;  //!< shifted volume address
            CxxSeries<Volume>   volumes; //!< slices
            MutableType * const data;    //!< all items

            //! setup slices
            inline void setup()
            {
                const Layout4D &fmt = **this;
                const unit_t    llo = fmt.lower.w;
                const unit_t    lup = fmt.upper.w;
                const size_t    ipv = fmt.shift.z; // items per volume
                MutableType *   ptr = data;
                for(unit_t l=llo;l<=lup;++l, ptr += ipv)
                {
                    const String uid = name + Formatted::Get("[%s]", Decimal(l).c_str() );
                    volumes.push(uid,volumeFormat,sliceFormat,rowFormat,ptr);
                }
                Coerce(volume) = &volumes[1] - llo;
            }
        };

    }

}

#endif

