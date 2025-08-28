//! \file


#ifndef Y_Chemical_Clusters_Included
#define Y_Chemical_Clusters_Included 1


#include "y/chemical/plexus/cluster.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Create list of clusters and update equilibria
        //
        //
        //______________________________________________________________________
        class Clusters : public CountedObject, public Ingress< Core::ListOf<Cluster> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Clusters"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Clusters(XMLog &, Equilibria &, const xreal_t t0 = 0.0); //!< full setup
            virtual ~Clusters() noexcept;             //!< cleanup

            void computeK(const xreal_t );

        private:
            Y_Disable_Copy_And_Assign(Clusters); //!< discarding
            Y_Ingress_Decl();        //!< helper
            CxxListOf<Cluster> list; //!< content
            XArray             topK; //!< top level K array

        public:
            const XReadable  &K;

        };
    }

}

#endif

