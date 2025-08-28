
//! \file


#ifndef Y_Chemical_Cluster_Included
#define Y_Chemical_Cluster_Included 1


#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef Protean::BareLightList<Equilibrium>   EList;
        typedef typename EList::NodeType              ENode;

        struct ListOps
        {
            template <typename LIST> inline static
            void Sort(LIST &list) noexcept
            {
                list.sort( Compare );
            }

            template <typename LIST> inline static
            void Indx(LIST &list, const Level L) noexcept
            {
                size_t i = 0;
                for(typename LIST::NodeType * node=list->head;node;node=node->next)
                {
                    Coerce( (**node).indx[L] ) = ++i;
                }
            }

            template <typename LIST> inline static
            void Make(LIST &list, const Level L) noexcept
            {
                Sort(list);
                Indx(list,L);
            }

            static
            SignType Compare(const Indexed & lhs, const Indexed & rhs) noexcept
            {
                return Sign::Of( lhs.indx[TopLevel], rhs.indx[TopLevel] );
            }
        };

        class Cluster :
        public Object,
        public Ingress<const EList>,
        public Assemblies
        {
        public:
            static const char * const CallSign;
            typedef AutoPtr<Conservation::Laws> CLaws;

            explicit Cluster(Equilibrium &first);
            virtual ~Cluster() noexcept;
            Y_OSTREAM_PROTO(Cluster);
            

            bool accepts(const Equilibrium &) const noexcept;
            bool accepts(const Cluster &) const noexcept;
            void attach(Equilibrium &);
            void fusion(Cluster * const) noexcept;
            void compile(XMLog &xml);


        private:
            Y_Disable_Copy_And_Assign(Cluster);
            Y_Ingress_Decl();
            void        attach(const Species &);
            void        update() noexcept;
            EList       elist;
        public:
            const SList   slist;
            const iMatrix iTopo; //!< integer topology matrix
            const uMatrix uCLaw; //!< unsigned conservation matrix
            const CLaws   claws; //!< list of conservations

            Cluster * next;
            Cluster * prev;

        private:
            void buildTopology(XMLog &);
            void buildConservations(XMLog &);
            void buildCombinatorics(XMLog &);
        };

    }

}

#endif

