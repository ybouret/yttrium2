
//! \file


#ifndef Y_Chemical_Solver_Included
#define Y_Chemical_Solver_Included 1


#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/plexus/solve1d.hpp"
#include "y/chemical/plexus/solver/prospect.hpp"
#include "y/ortho/house.hpp"
#include "y/mkl/algebra/lu.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //typedef Protean::SoloLightList<const Species> SpList;

        //______________________________________________________________________
        //
        //
        //
        //! non-linear mutli-stage solver for one cluste
        //
        //
        //______________________________________________________________________
        class Solver
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Solver(const Cluster &);
            virtual ~Solver() noexcept;

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________

            typedef xreal_t (Solver::*Proc)(XMLog &);

            //! build valid prospects and initialize Wsub/Csub
            /**
             \param xml output
             \param Ctop initial top-level concentrations, may be modified
             \param Ktop initial top-level constants
             \return true iff more than one prospect
             */
            bool    proceed(XMLog &xml, XWritable & Ctop, const XReadable & Ktop);


            xreal_t explore(XMLog &xml);
            xreal_t kinetic(XMLog &xml);
            void    forward(XMLog &xml, XWritable & Ctop, const XReadable & Ktop);
            bool    upgrade(XMLog &xml, const String &uuid, Proc meth);

            //!  \return rms of affinitie
            xreal_t affinityRMS(const XReadable &, const Level);

            //! store individual components in affinity \return rms
            xreal_t fullAffinityRMS(const XReadable &, const Level);

            //! \param u in [0:1] \return affinity at Ctry = (1-u) * Csub + u * Cend
            xreal_t operator()(xreal_t u);


            //! minimize from Wsub/Csub to Cend with recomputed affinity
            xreal_t minimize(XMLog &xml);

            void    savePro(const String &baseName, const unsigned);

        private:
            Y_Disable_Copy_And_Assign(Solver); //!< discarding

            const Cluster &       cluster;
            xreal_t               Wsub;         //!< SubLevel W
            XArray                Csub;         //!< SubLevel C
            XArray                Cend;         //!< endpoint on concetration
            XArray                Ctry;         //!< probe
            xreal_t               Wnew;         //!< SubLevel new W
            XArray                Cnew;         //!< SubLevel new C
            XArray                dC;           //!< delta C helper
            XMatrix               Ceq;          //!< storage for prospect/solve1d
            XArray                affinity;     //!< storage for affinites
            PPool                 ppool;        //!< shared pool for prospects
            PList                 plist;        //!< active equilibria
            xreal_t               psize;        //!< |plist| in xreal
            PList                 basis;        //!< selected basis
            XAdd                  xadd;         //!< helper for affinities
            XAdd                  xsum;         //!< helper for affinityRMS
            Solve1D               solve1d;      //!< solving each equilibria
            Accumulator           xkin;         //!< accumulator
            AutoPtr<Ortho::House> house;        //!< extract basis
            MKL::LU<xreal_t>      lu;           //!< for algebra
            const xreal_t         zero;         //!< alias
            const xreal_t         one;          //!< alias
            const xreal_t         safety;       //!< safety coefficient
            const String          proExt;       //!< "pro"
            String                gnuplot;      //!< constructed gnuplot command
            const String          exploreName;  //!< "explore"
            const String          kineticName;  //!< "kinetric"
            

        };


    }

}

#endif
