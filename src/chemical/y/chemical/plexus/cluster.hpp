
//! \file


#ifndef Y_Chemical_Cluster_Included
#define Y_Chemical_Cluster_Included 1


#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Protean::BareLightList<Equilibrium>   EList; //!< alias
        typedef typename EList::NodeType              ENode; //!< alias

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

        };

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
            bool accepts(const Equilibrium &) const noexcept; //!< \return true if one of my species in equilibrium
            bool accepts(const Cluster &)     const noexcept; //!< \return true if at least one shared species
            void attach(Equilibrium &);                       //!< add equilibrium and its species
            void fusion(Cluster * const) noexcept;            //!< add cluster's content
            void compile(XMLog &);                            //!< compile once setup


        private:
            Y_Disable_Copy_And_Assign(Cluster);  //!< discarding
            Y_Ingress_Decl();                    //!< helper
            void        attach(const Species &); //!< check/insert
            void        update() noexcept;       //!< update sublevel status

            EList         elist; //!< my equilibria
        public:
            const SList   slist; //!< my species
            const iMatrix iTopo; //!< integer topology matrix
            const uMatrix uCLaw; //!< unsigned conservation matrix
            const CLaws   claws; //!< list of conservations
            Cluster *     next;  //!< for list
            Cluster *     prev;  //!< for list

        private:
            void buildTopology(XMLog &);      //!< build topology
            void buildConservations(XMLog &); //!< build conservations
            void buildCombinatorics(XMLog &); //!< build combinatorics
        };

    }

}

#endif

