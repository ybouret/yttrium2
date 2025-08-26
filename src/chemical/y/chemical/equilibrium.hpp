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
        //! Base class for equilibria
        //
        //
        //______________________________________________________________________
        class Equilibrium : public Components
        {
        public:
            static const char * const CallSign; //!< "Equilibrium"

        protected:
            template <typename ID> inline
            explicit Equilibrium(const ID & id, const size_t top) :
            Components(id,top)
            {
            }

        public:
            virtual ~Equilibrium() noexcept;

            xreal_t K(const xreal_t);

        private:
            Y_Disable_Copy_And_Assign(Equilibrium); //!< discarding
            virtual xreal_t getK(const xreal_t) = 0;
        };


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
            template <typename ID> inline
            explicit ConstEquilibrium(const ID & id, const xreal_t KK, const size_t top) :
            Equilibrium(id,top), K_(KK)
            {
            }

            virtual ~ConstEquilibrium() noexcept;

        private:
            Y_Disable_Copy_And_Assign(ConstEquilibrium);
            virtual xreal_t getK(const xreal_t);

            const xreal_t K_;
        };


    }

}

#endif

