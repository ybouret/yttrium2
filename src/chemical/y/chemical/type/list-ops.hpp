
//! \file


#ifndef Y_Chemical_ListOps_Included
#define Y_Chemical_ListOps_Included 1



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
    }

}

#endif

