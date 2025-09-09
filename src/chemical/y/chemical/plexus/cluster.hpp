
//! \file


#ifndef Y_Chemical_Cluster_Included
#define Y_Chemical_Cluster_Included 1


#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {



        


        class Clusters;

        //______________________________________________________________________
        //
        //
        //
        //! Cluster of linked species and equilibria
        //
        //
        //______________________________________________________________________
        class Cluster :
        public Object,
        public Ingress<const EList>,
        public Assemblies
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const           CallSign; //!< "Cluster"
            static const char * const           CSID;     //!< "set19"
            typedef AutoPtr<Conservation::Laws> CLaws;    //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Cluster(Equilibrium &first); //!< setup \param first first equilibrium
            virtual ~Cluster() noexcept;          //!< cleanup
            Y_OSTREAM_PROTO(Cluster);             //!< display


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! compute top-level K at given t
            /**
             \param K top level constants
             \param t time of evaluation
             */
            void compute(XWritable &K, const xreal_t t);

            //! import/export species data
            /**
             \param C target
             \param L target level
             \param C0 source
             \param L0 source level
             */
            void copy(XWritable &C, const Level L, const XReadable &C0, const Level L0) const;

            //! \param Csub sub-level array \param Ctop top-level array
            void dowload(XWritable &Csub, const XReadable &Ctop) const;

            //! \param Csub sub-level array \param Ctop top-level array
            void upload(XWritable &Ctop, const XReadable &Csub) const;

            //__________________________________________________________________
            //
            //
            // GraphViz methods
            //
            //__________________________________________________________________
            OutputStream & viz(OutputStream &fp, const size_t numOrder) const;
            void           vizSpecies(OutputStream &) const;

        private:
            Y_Disable_Copy_And_Assign(Cluster);  //!< discarding
            Y_Ingress_Decl();                    //!< helper
            friend class Clusters;
            bool accepts(const Equilibrium &) const noexcept; //!< \return true if one of my species in equilibrium
            bool accepts(const Cluster &)     const noexcept; //!< \return true if at least one shared species
            void attach(Equilibrium &);                       //!< add equilibrium and its species
            void fusion(Cluster * const) noexcept;            //!< add cluster's content
            void attach(const Species &);                      //!< check/insert
            void update() noexcept;                            //!< update sublevel status

            void compile(XMLog &, Equilibria &, const XReadable &); //!< compile once setup

            EList           elist; //!< my equilibria
        public:
            const SList     slist;     //!< my species
            const iMatrix   iTopo;     //!< initial integer topology matrix
            const uMatrix   uCLaw;     //!< unsigned conservation matrix
            const CLaws     claws;     //!< list of conservations
            const SList     conserved; //!< conserved species
            const SList     unbounded; //!< unbounded species
            const EList     standard;  //!< with at least an unbounded species on each side
            const EList     prodOnly;  //!< with only products
            const EList     reacOnly;  //!< with only reactants
            const EList     nebulous;  //!< with unbounded only
            const iMatrix   iFull;     //!< full topology, ints
            const XMatrix   xFull;     //!< full topology, xreals
            CxxArray<EList> order;     //!< different combination order

            const unsigned indx;  //!< indx
            Cluster *      next;  //!< for list
            Cluster *      prev;  //!< for list
            
            const GraphViz::ColorScheme & cs;

        private:
            void buildTopology(XMLog &);      //!< build topology
            void buildConservations(XMLog &); //!< build conservations
            void buildCombinatorics(XMLog &,Equilibria&,const XReadable &); //!< build combinatorics
        };

    }

}

#endif

