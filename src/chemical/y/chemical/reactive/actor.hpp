//! \file


#ifndef Y_Chemical_Actor_Included
#define Y_Chemical_Actor_Included 1


#include "y/chemical/species.hpp"
#include "y/chemical/type/xreal.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Actor = nu + sp
        //
        //
        //______________________________________________________________________
        class Actor : public Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const   CallSign; //!< "Actor"
            typedef CxxListOf<Actor>    List;     //!< alias
            typedef Core::ListOf<Actor> CoreList; //!< alias

            //! role for formating
            enum Role
            {
                InEquilibrium,      //!< define equilibium
                InConservation      //!< define conservationlaw
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            explicit Actor(const unsigned,
                           const Species &,
                           const Role = InEquilibrium);
            virtual ~Actor() noexcept; //!< cleanup
            Actor(const Actor &);      //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param X xmul, updated \param C concentrations \param L level
            void massAction(XMul &X, const XReadable &C, const Level L) const;

            //! \param X xmul, updated at xi \param C concentrations \param L level \param xi extent 
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const;

            //! \param X xmul, updated for derivatives \param C concentrations \param L level
            void diffAction(XMul &X, const XReadable &C, const Level L) const;

            //! move safely \param C concentrations \param L level \param xi extent
            void moveSafely(XWritable &C, const Level L, const xreal_t xi) const;

            String html() const; //! \return as html concentration

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Species &sp;   //!< species
            const unsigned nu;   //!< stoichio
            const xreal_t  xn;   //!< stoichio as xreal
            const xreal_t  xn2;  //!< xn*xn*
            const unsigned nu1;  //!< nu-1
            Actor *        next; //!< for list
            Actor *        prev; //!< for list
            const xreal_t  zero; //!< named constant
            
        private:
            Y_Disable_Assign(Actor); //!< discarding
        };
    }

}

#endif

