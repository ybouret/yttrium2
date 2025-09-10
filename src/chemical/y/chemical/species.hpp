
//! \file


#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1


#include "y/chemical/type/indexed.hpp"
#include "y/chemical/formula.hpp"
#include "y/pointer/keyed.hpp"
#include "y/protean/bare/light/list.hpp"
#include "y/protean/solo/light/list.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Species decription
        //
        //
        //______________________________________________________________________
        class Species : public Indexed, public Formula, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Keyed< String, ArcPtr<Species> > Pointer; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Species(const Formula &,    const size_t); //!< setup
            explicit Species(const String &,     const size_t); //!< setup
            explicit Species(const char * const, const size_t); //!< setup
            virtual ~Species() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! emit GraphViz code
            /**
             \param fp output stream
             \param color precomputed color
             \param style precomputed style
             \return output stream
             */
            OutputStream & viz(OutputStream &     fp,
                               const String &     color,
                               const char * const style) const;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const int z; //!< algebraic charge
        private:
            Y_Disable_Copy_And_Assign(Species);  //!< discarding
        };

        typedef Protean::BareLightList<const Species> SList; //!< alias
        typedef typename SList::NodeType              SNode; //!< alias
        typedef Protean::SoloLightList<const Species> SRepo; //!< alias

    }

}

#endif

