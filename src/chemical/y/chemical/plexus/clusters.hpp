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
            explicit Clusters(XMLog &, Equilibria &, const xreal_t = 0.0); //!< full setup
            virtual ~Clusters() noexcept;                                  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void computeK(const xreal_t ); //!< compute inner K

            void viz(const String &root, const size_t numOrder) const;


        private:
            Y_Disable_Copy_And_Assign(Clusters); //!< discarding
            Y_Ingress_Decl();        //!< helper
            CxxListOf<Cluster> list; //!< content
            XArray             topK; //!< top level K array

        public:
            const XReadable    &K;   //!< top level K reference
            const size_t        maxOrder; //!< maximum order over all clusters
        };
    }

}

#endif // !Y_Chemical_Clusters_Included

