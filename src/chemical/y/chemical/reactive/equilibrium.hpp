//! \file

#ifndef Y_Chemical_Equilibrium_Included
#define Y_Chemical_Equilibrium_Included 1


#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {


     

        //______________________________________________________________________
        //
        //
        //
        //! Base class for equilibria = components + constant
        //
        //
        //______________________________________________________________________
        class Equilibrium : public Components
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const                   CallSign; //!< "Equilibrium"
            typedef Keyed< String,ArcPtr<Equilibrium> > Pointer; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup \param id name \param top top-level index
            template <typename ID> inline
            explicit Equilibrium(const ID & id, const size_t top) :
            Components(id,top)
            {
            }

        public:
            virtual ~Equilibrium() noexcept; //!< cleanup

            //! display name only
            inline friend std::ostream & operator<<(std::ostream &os, const Equilibrium &eq)
            {
                return os << eq.name;
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            xreal_t K(const xreal_t); //!< \return tested constant



        private:
            Y_Disable_Copy_And_Assign(Equilibrium);  //!< discarding
            virtual xreal_t getK(const xreal_t) = 0; //!< \return constant at given time
        };

        typedef Protean::BareLightList<Equilibrium>   EList; //!< alias
        typedef EList::NodeType                       ENode; //!< alias
        typedef Protean::SoloLightList<Equilibrium>   ERepo; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! ConstEquilibrium
        //
        //
        //______________________________________________________________________
        class ConstEquilibrium : public Equilibrium
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id name \param KK constant value \param top top-level index
            template <typename ID> inline
            explicit ConstEquilibrium(const ID & id, const xreal_t KK, const size_t top) :
            Equilibrium(id,top), K_(KK)
            {
            }

            virtual ~ConstEquilibrium() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(ConstEquilibrium); //!< discarding
            virtual xreal_t getK(const xreal_t);
            const xreal_t K_; //!< the constant
        };


    }

}

#endif

