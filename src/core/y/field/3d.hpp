
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
            template <typename UID>
            inline explicit In3D(const UID &      uid,
                                 const Format3D & fmt) :
            Sketch(uid,fmt->items * sizeof(T)),
            Format3D(fmt),
            sliceFormat( new Layout2D(SubLayout,**this) ),
            rowFormat(   new Layout1D(SubLayout,*sliceFormat) ),
            slice(0),
            slices( fmt->numSlices() ),
            data( (MutableType *)wksp )
            {
                setup();
            }

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
            inline std::ostream & print(std::ostream &os, size_t indent) const
            {
                const Layout3D & fmt = **this;
                Core::Indent(os,indent<<1) << fmt << ":" << std::endl;
                ++indent;
                for(unit_t k=fmt.lower.z;k<=fmt.upper.z;++k)
                {
                    //slice[k].print(os,indent);
                    if(k<fmt.upper.z) os << std::endl;
                }
                return os;
            }


            const Format2D sliceFormat;
            const Format1D rowFormat;

        private:
            Y_Disable_Copy_And_Assign(In3D);
            Slice * const       slice;
            CxxSeries<Slice>    slices;
            MutableType * const data;

            inline void setup()
            {
                std::cerr << "items=" << (*this)->items << std::endl;
                const unit_t  klo = (*this)->lower.z;
                const unit_t  kup = (*this)->upper.z;
                const size_t  ips = (*this)->shift.y; // items per slice
                MutableType * ptr = data;
                std::cerr << "ips=" << ips << std::endl;
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

