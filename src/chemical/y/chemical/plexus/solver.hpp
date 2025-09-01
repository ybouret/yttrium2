
//! \file


#ifndef Y_Chemical_Solver_Included
#define Y_Chemical_Solver_Included 1


#include "y/chemical/plexus/cluster.hpp"
#include "y/chemical/plexus/solve1d.hpp"
#include "y/chemical/plexus/solver/prospect.hpp"

namespace Yttrium
{
    namespace Chemical
    {


        class Solver
        {
        public:
            explicit Solver(const Cluster &);
            virtual ~Solver() noexcept;

            void buildProspects(XMLog &           xml,
                                XWritable &       Ctop,
                                const XReadable & Ktop);

            //! store individual components in affinity \return rms
            xreal_t affinityRMS(const XReadable &, const Level);
            xreal_t operator()(xreal_t u);

        private:
            const Cluster &cluster;
            XArray         Csub;
            XArray         Cend;
            XArray         Ctry;
            XMatrix        Ceq;
            PList          plist;
            xreal_t        psize;
            XArray         affinity;
            XAdd           xadd;
            XAdd           xsum;
            Solve1D        solve1d;
            const xreal_t  zero;
            const xreal_t  one;

            void optimize(XMLog &xml, Prospect &pro, const xreal_t Wsub);

        };

        
    }

}

#endif
