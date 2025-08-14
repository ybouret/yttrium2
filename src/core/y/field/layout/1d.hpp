//! \file

#ifndef Y_Field_Layout_In1D_Included
#define Y_Field_Layout_In1D_Included 1

#include "y/field/layout.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{

    namespace Field
    {
        typedef unit_t                  Coord1D;   //!< alias
        typedef size_t                  Count1D;   //!< alias
        typedef Layout<Coord1D,Count1D> Layout1D_; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! 1D Layout
        //
        //
        //______________________________________________________________________
        class Layout1D : public Layout1D_
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            
            //! setup \param lo lower coordinate \param up upper coordinates
            explicit Layout1D(const Coord1D lo, const Coord1D up) noexcept;

            //! setup \param _ helper \param super super layout
            template <typename SUPER> inline
            explicit Layout1D(const SubLayout_ &_, const SUPER &super) noexcept :
            Layout1D_(_,super)
            {
            }

            //! cleanup
            virtual ~Layout1D() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Layout1D); //!< discarding
        };

        typedef ArcPtr<const Layout1D>  Format1D; //!< alias;



    }

}

#endif

