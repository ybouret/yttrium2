//! \file

#ifndef Y_Associative_KnotList_Included
#define Y_Associative_KnotList_Included 1

#include "y/core/linked/list.hpp"
#include "y/container/iter/linked.hpp"
#include "y/container.hpp"

namespace Yttrium
{

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Master components for associative
        //
        //
        //______________________________________________________________________
        template <typename KNOT>
        class MasterOf : public Container
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename KNOT::List                    KList;         //!< alias
            typedef typename KNOT::Pool                    KPool;         //!< alias
            typedef Iter::Linked<Iter::Forward,KNOT>       Iterator;      //!< alias
            typedef Iter::Linked<Iter::Forward,const KNOT> ConstIterator; //!< alias


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t size() const noexcept { return list.size; } //!< \return container size

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Iterator      begin()       noexcept { return list.head; } //!< \return begin
            inline Iterator      end()         noexcept { return 0; }         //!< \return end
            inline ConstIterator begin() const noexcept { return list.head; } //!< \return begin
            inline ConstIterator end()   const noexcept { return 0; }         //!< \return end


            //! display \param os output stream \param self *this \return os
            inline friend std::ostream & operator<<(std::ostream &os, const MasterOf &self)
            {
                os << '{';
                const KNOT *knot = self.list.head;
                if(knot)
                {
                    os << *knot;
                    for(knot=knot->next;knot;knot=knot->next)
                    {
                        os << ',' << *knot;
                    }
                }
                return os << '}';
            }

            template <typename COMPARE_DATA>
            void sort(COMPARE_DATA &compareData)
            {
                list.sortWith(compareData);
            }

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline virtual ~MasterOf() noexcept {} //!< cleanup

        protected:
            //! setup
            inline explicit MasterOf() noexcept : list(), pool() {}

            //__________________________________________________________________
            //
            //
            // common helpers
            //
            //__________________________________________________________________

            //! return list to pool
            inline void clearList() noexcept
            {
                while(list.size) pool.banish(list.popTail());
            }

            //! remove list
            inline void  purgeList() noexcept
            {
                while(list.size) pool.remove(list.popTail());
            }

            //__________________________________________________________________
            //
            //
            //  Members
            //
            //__________________________________________________________________
            KList list; //!< list of knots
            KPool pool; //!< pool for knots

        private:
            Y_Disable_Copy_And_Assign(MasterOf); //!< discarding
        };
    }
}

#endif

