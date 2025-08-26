//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1


#include "y/chemical/reactive/actors.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base class for Equilibrium
        //
        //
        //______________________________________________________________________
        class Components : public Indexed
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const Arrows;   //!< "<=>"
            static const char * const Prod;     //!< "Prod"
            static const char * const Reac;     //!< "Reac"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup \param id name \param top top-level index
            template <typename ID> inline
            explicit Components(const ID & id, const size_t top) :
            Indexed(id,top),
            reac(),
            prod()
            {
            }
            virtual ~Components() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Components);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void p(const unsigned, const Species &); //!< add product
            void r(const unsigned, const Species &); //!< add reactant
            void p(const Species &); //!< add product
            void r(const Species &); //!< add reactant

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Actors reac; //!< reactants
            const Actors prod; //!< products
        private:
            Y_Disable_Copy_And_Assign(Components); //!< discarding
        };
    }

}

#endif

