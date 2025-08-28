
//! \file


#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1


#include "y/chemical/type/indexed.hpp"
#include "y/chemical/formula.hpp"
#include "y/pointer/keyed.hpp"
#include "y/protean/bare/light/list.hpp"


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
        class Species : public Indexed, public Formula
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
            // Members
            //
            //__________________________________________________________________
            const int z; //!< algebraic charge
        private:
            Y_Disable_Copy_And_Assign(Species);  //!< discarding
        };

        typedef Protean::BareLightList<const Species> SList;
        typedef typename SList::NodeType              SNode;

    }

}

#endif

