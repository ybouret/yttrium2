
//! \file

#ifndef Y_Field_2D_Included
#define Y_Field_2D_Included 1

#include "y/field/1d.hpp"
#include "y/field/layout/2d.hpp"
#include "y/container/cxx/series.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! 2D Field
        //
        //
        //______________________________________________________________________
        template <typename T>
        class In2D : public Sketch, public Format2D
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
            inline explicit In2D(const UID &      uid,
                                 const Format2D & fmt) :
            Sketch(uid, fmt->items * sizeof(T) ),
            Format2D(fmt),
            rowFormat(  new Layout1D(SubLayout,**this) ),
            row(0),
            rows( fmt->width.y )
            {
                setup();
            }

            //! cleanup
            inline virtual ~In2D() noexcept
            {
            }

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const In2D &f)
            {
                const Layout2D &fmt = *f;
                os << f.name << "=" << fmt;
                return os;
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param j row index \return row[j]
            inline Row & operator[](const unit_t j) noexcept
            {
                assert(j>= (*this)->lower.y);
                assert(j<= (*this)->upper.y);
                return row[j];
            }

            //! \param j row index \return row[j]
            inline const Row & operator[](const unit_t j) const noexcept
            {
                assert(j>= (*this)->lower.y);
                assert(j<= (*this)->upper.y);
                return row[j];
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Format1D rowFormat; //!< shared row format

        private:
            Y_Disable_Copy_And_Assign(In2D); //!< discarding
            Row * const    row;  //!< row location, shifted
            CxxSeries<Row> rows; //!< constructed rows

            //! setup all rows from memory
            void setup()
            {
                const size_t  nx = (*this)->width.x;
                const size_t  ny = (*this)->width.y;
                MutableType * p  = (MutableType*) wksp;
                for(size_t j=1;j<=ny;++j, p += nx)
                {
                    const String uid = name + Formatted::Get("[%s]", Decimal(j).c_str() );
                    rows.push(uid,rowFormat,p);
                }
                Coerce(row) = &rows[1] - (*this)->lower.y;
            }
        };
    }

}

#endif
