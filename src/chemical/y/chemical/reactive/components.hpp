//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1


#include "y/chemical/reactive/actors.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        enum MatterFlow
        {
            Dangling,
            BothWays,
            ProdOnly,
            ReacOnly,
        };

        //______________________________________________________________________
        //
        //
        //
        //! Base class for Equilibrium
        //
        //
        //______________________________________________________________________
        class Components : public Indexed, public Freezable
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
            static const char         Prefix = '@';
            
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
            prod(),
            flow(Dangling),
            xdim(0)
            {
            }
            virtual ~Components() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Components);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods to setup
            //
            //__________________________________________________________________
            void p(const unsigned, const Species &); //!< add product
            void r(const unsigned, const Species &); //!< add reactant
            void p(const Species &); //!< add product
            void r(const Species &); //!< add reactant

            bool neutral() const;

            //__________________________________________________________________
            //
            //
            // Methods to compute
            //
            //__________________________________________________________________
            xreal_t massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L) const;
            xreal_t massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L, const real_t xi) const;
            void    moveSafely(XWritable &C, const Level L, const xreal_t xi) const;

            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Actors      reac; //!< reactants
            const Actors      prod; //!< products
            const MatterFlow  flow; //!< current flow
            const xreal_t     xdim; //!< components in xreal_t
        private:
            Y_Disable_Copy_And_Assign(Components); //!< discarding
            void updateFlow() noexcept;
        };
    }

}

#endif

