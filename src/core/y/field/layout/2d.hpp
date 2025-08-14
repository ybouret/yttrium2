//! \file

#ifndef Y_Field_Layout_In2D_Included
#define Y_Field_Layout_In2D_Included 1

#include "y/field/layout.hpp"
#include "y/mkl/v2d.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{

    namespace Field
    {
        typedef V2D<unit_t>             Coord2D;  //!< alias
        typedef V2D<size_t>             Count2D;  //!< alias
        typedef Layout<Coord2D,Count2D> Layout2D_; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! 2D Layout
        //
        //
        //______________________________________________________________________
        class Layout2D : public Layout2D_
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
          
            //! setup \param lo lower coordinate \param up upper coordinates
            explicit Layout2D(const Coord2D lo, const Coord2D up) noexcept;

            //! setup \param _ helper \param super super layout
            template <typename SUPER> inline
            explicit Layout2D(const SubLayout_ &_, const SUPER &super) noexcept :
            Layout2D_(_,super)
            {
            }

            //! cleanup
            virtual ~Layout2D() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            size_t numRows() const noexcept; //!< \return width.y


        private:
            Y_Disable_Copy_And_Assign(Layout2D); //!< discarding

        };


        typedef ArcPtr<const Layout2D>  Format2D; //!< alias

    }

}

#endif

