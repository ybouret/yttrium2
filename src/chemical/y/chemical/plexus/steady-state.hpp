
//! \file


#ifndef Y_Chemical_SteadyState_Included
#define Y_Chemical_SteadyState_Included 1


#include "y/chemical/plexus/solver.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Compute steady state for clusters
        //
        //
        //______________________________________________________________________
        class SteadyState : public Object, public Ingress< Core::ListOf<Solver> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit SteadyState(const Clusters &); //!< setup
            virtual ~SteadyState() noexcept;        //!< cleanu[

            //! solve with inner clusters K, which must be up to date
            /**
             \param xml output
             \param Ctop top-level concentrations, updated
             */
            void solve(XMLog &xml, XWritable & Ctop);

        private:
            Y_Disable_Copy_And_Assign(SteadyState); //!< discarding
            Y_Ingress_Decl();                       //!< helper
            CxxListOf<Solver>  solvers;             //!< one solver per cluster
            const Clusters   & clusters;            //!< persistent clusters
        };
    }
}

#endif

