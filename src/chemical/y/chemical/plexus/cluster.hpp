
//! \file


#ifndef Y_Chemical_Cluster_Included
#define Y_Chemical_Cluster_Included 1


#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {



        //! helper to handle lists
        struct ListOps
        {
            //! sort by top level index \param list compatible list
            template <typename LIST> inline static
            void Sort(LIST &list) noexcept {
                list.sort( Compare );
            }

            //! index given level \param list compatible list \param L target level
            template <typename LIST> inline static
            void Indx(LIST &list, const Level L) noexcept
            {
                size_t i = 0;
                for(typename LIST::NodeType * node=list->head;node;node=node->next)
                {
                    Coerce( (**node).indx[L] ) = ++i;
                }
            }

            //! sort and index \param list compatible list \param L target level
            template <typename LIST> inline static
            void Make(LIST &list, const Level L) noexcept
            {
                Sort(list);
                Indx(list,L);
            }

            //! \return top level indices comparison
            static SignType Compare(const Indexed &, const Indexed &) noexcept;

            //! import/export data
            /**
             \param slist    species list
             \param target   target array
             \param tgtLevel target level
             \param source   source array
             \param srcLevel source level
             */
            static   void Copy(const SList     & slist,
                               XWritable       & target,
                               const Level       tgtLevel,
                               const XReadable & source,
                               const Level       srcLevel)
            {
                for(const SNode *sn=slist->head;sn;sn=sn->next)
                {
                    const Species &sp = **sn;
                    sp(target,tgtLevel) = sp(source,srcLevel);
                }
            }



        };


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

            void dowload(XWritable &Csub, const XReadable &Ctop) const;
            void upload(XWritable &Ctop, const XReadable &Csub) const;


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
            const iMatrix   iFull;     //!< full topology
            CxxArray<EList> order;     //!< different combination order


            Cluster *     next;  //!< for list
            Cluster *     prev;  //!< for list

        private:
            void buildTopology(XMLog &);      //!< build topology
            void buildConservations(XMLog &); //!< build conservations
            void buildCombinatorics(XMLog &,Equilibria&,const XReadable &); //!< build combinatorics
        };

    }

}

#endif

