
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
            rows( fmt->numRows() ),
            data( (MutableType *) wksp )
            {
                setup();
            }

            //! slice within 3D
            /**
             \param uid     name
             \param fmt     Format2D
             \param rowFmt  Format1D
             \param slice   memory
             */
            template <typename UID>
            inline explicit In2D(const UID &         uid,
                                 const Format2D &    fmt,
                                 const Format1D &    rowFmt,
                                 MutableType * const slice) :
            Sketch(uid),
            Format2D(fmt),
            rowFormat(rowFmt),
            row(0),
            rows( fmt->numRows() ),
            data( (MutableType *) slice )
            {
                setup();
            }

            //! cleanup
            inline virtual ~In2D() noexcept {}

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const In2D &f)
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
                const Layout2D & fmt = **this;
                Core::Indent(os,indent<<1) << name << "@" << fmt << ":" << std::endl;
                ++indent;
                for(unit_t j=fmt.lower.y;j<=fmt.upper.y;++j)
                {
                    row[j].print(os,indent);
                    if(j<fmt.upper.y) os << std::endl;
                }
                return os;
            }


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
            Row * const         row;  //!< row location, shifted
            CxxSeries<Row>      rows; //!< constructed rows
            MutableType * const data; //!< memory

            //! setup all rows from memory
            void setup()
            {
                const size_t  ipr = (*this)->width.x; // items per row
                const unit_t  jlo = (*this)->lower.y;
                const unit_t  jup = (*this)->upper.y;
                MutableType * ptr = data;
                for(unit_t j=jlo;j<=jup;++j, ptr += ipr)
                {
                    const String uid = name + Formatted::Get("[%s]", Decimal(j).c_str() );
                    rows.push(uid,rowFormat,ptr);
                }
                Coerce(row) = &rows[1] - jlo;
            }
        };
    }

}

#endif
