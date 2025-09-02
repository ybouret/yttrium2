//! \file


#ifndef Y_Chemical_Prospect_Included
#define Y_Chemical_Prospect_Included 1

#include "y/chemical/reactive/equilibrium.hpp"
#include "y/protean/solo/heavy/list.hpp"
#include "y/chemical/type/assembly.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! active and valid equilibria
        //
        //
        //______________________________________________________________________
        class Prospect
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param _st initial status
             \param _eq equilibrium
             \param _eK pre-computed constant
             \param _cc solve1d phase space
             \param _xi from original phase space
             */
            Prospect(const Status        _st,
                     const Equilibrium & _eq,
                     const xreal_t       _eK,
                     XWritable &         _cc,
                     xreal_t             _xi) noexcept;


            Prospect(const Prospect &) noexcept; //!< duplicate
            ~Prospect() noexcept;                //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! pretty display \return ostream
            std::ostream & display(std::ostream &, const Assembly &) const;

            //! \return decreasing |xi|
            static SignType ByDecreasingXi(const Prospect &, const Prospect &) noexcept;

            //! \return increasing Wo
            static SignType ByIncreasingWo(const Prospect &, const Prospect &) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Status       st;   //!< status
            const Equilibrium &eq;   //!< equilibrium
            const xreal_t      eK;   //!< current e.K
            XWritable &        cc;   //!< optimized phases space
            xreal_t            xi;   //!< optimized extent
            xreal_t            W0;   //!< original  W
            xreal_t            Wo;   //!< optimized W
            xreal_t            W1;   //!< solve1d   W

        private:
            Y_Disable_Assign(Prospect); //!< discarding
        };

        typedef List<Prospect>  PList; //!< alias
        typedef PList::NodeType PNode; //!< alias
    }

}

#endif

