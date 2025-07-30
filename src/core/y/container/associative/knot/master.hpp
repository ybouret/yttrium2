//! \file

#ifndef Y_Associative_KnotList_Included
#define Y_Associative_KnotList_Included 1

#include "y/core/linked/list.hpp"
#include "y/container/iter/linked.hpp"

namespace Yttrium
{

    namespace Core
    {
        template <typename KNOT>
        class MasterOf
        {
        public:
            typedef typename KNOT::List KList;
            typedef typename KNOT::Pool KPool;

            typedef Iter::Linked<Iter::Forward,KNOT>       Iterator;
            typedef Iter::Linked<Iter::Forward,const KNOT> ConstIterator;

            inline Iterator      begin()       noexcept { return list.head; }
            inline Iterator      end()         noexcept { return 0; }
            inline ConstIterator begin() const noexcept { return list.head; }
            inline ConstIterator end()   const noexcept { return 0; }

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

            virtual ~MasterOf() noexcept {}

        protected:
            inline explicit MasterOf() noexcept : list(), pool() {}


            inline void clearList() noexcept
            {
                while(list.size) pool.banish(list.popTail());
            }

            inline void  purgeList() noexcept
            {
                while(list.size) pool.remove(list.popTail());
            }

            KList list;
            KPool pool;
        private:
            Y_Disable_Copy_And_Assign(MasterOf);
        };
    }
}

#endif

