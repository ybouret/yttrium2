//! \file

#ifndef Y_Coven_IList_Included
#define Y_Coven_IList_Included 1

#include "y/protean/coop/heavy/list.hpp"


namespace Yttrium
{

    namespace Coven
    {



        typedef Protean::CoopHeavyList<size_t,SingleThreadedClass> IListType; //!< alias
        typedef IListType::PoolType                                IPool;     //!< alias
        typedef IListType::NodeType                                INode;     //!< aluas


        //______________________________________________________________________
        //
        //
        //
        //! List of indices
        //
        //
        //______________________________________________________________________
        class IList : public IListType
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit IList(const IPool &) noexcept; //!< empty list
            virtual ~IList() noexcept;              //!< cleanup
            IList(const IList &);                   //!< duplicate

            //! create list with pre-ordered items
            /**
             \param count list will contain 1..count
             \param first first index in 1..count
             */
            explicit IList(const IPool &, const size_t count, const size_t first);


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void remove(const size_t indx) noexcept;
            void sorted(const size_t indx);

            friend bool operator==(const IList &, const IList&) noexcept;




        private:
            Y_Disable_Assign(IList); //!< discarding
        };

        

    }

}
#endif

