#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/cxx/series.hpp"
#include "y/sorting/heap.hpp"

#include <cmath>

using namespace Yttrium;

namespace Yttrium
{
    struct Disperse
    {
        template <typename POSITION>
        class Item
        {
        public:
            inline   Item(const size_t i, const POSITION &p) :
            idx(i), pos(p)
            {
            }

            inline Item(const Item &_) : idx(_.idx), pos(_.pos) {}

            inline ~Item() noexcept
            {
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Item &item)
            {
                return os << '#' << item.idx << '@' << item.pos;
            }

            const size_t   idx;
            const POSITION pos;

        private:
            Y_Disable_Assign(Item);
        };

        template <
        typename POSITION,
        typename DISTANCE>
        class Pair
        {
        public:
            typedef Item<POSITION> ItemType;

            template <typename PROC>
            inline Pair(PROC &proc, const ItemType &lhsItem, const ItemType &rhsItem) :
            lhs(lhsItem),
            rhs(rhsItem),
            delta( proc(lhs.pos,rhs.pos) )
            {
            }

            inline Pair(const Pair &_) : lhs(_.lhs), rhs(_.rhs), delta(_.delta) {}

            inline ~Pair() noexcept
            {
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Pair &pair)
            {
                return os << '|' << pair.lhs << ':' << pair.rhs << '|' << '=' << pair.delta;
            }

            static inline
            SignType Compare(const Pair &lhs, const Pair &rhs)
            {
                return Sign::Of(lhs.delta,rhs.delta);
            }


            const ItemType &lhs;
            const ItemType &rhs;
            const DISTANCE  delta;

        private:
            Y_Disable_Assign(Pair);
        };


        static
        size_t Select(const size_t n) noexcept
        {
            assert(n>0);
            if( 0 == (n&1) )
            {
                // even
                return (n >> 1);
            }
            else
            {
                // odd
                assert( 1 == (n&1) );
                return 1 + ( (n-1) >> 1);
            }
        }


        template <typename ITEM> static inline
        void RemoveItem(const size_t idx, CxxSeries<ITEM> &items)
        {
            for(size_t i=items.size();i>0;--i)
            {
                ITEM &item = items[i];
                if(idx == item.idx)
                {
                }
            }
        }

        template <typename POSITION, typename DISTANCE, typename PROC> static inline
        void Make(TypeToType<DISTANCE>, Writable<size_t> &idx, PROC &proc, const Readable<POSITION> &pos)
        {
            typedef Item<POSITION>          ItemType;
            typedef Pair<POSITION,DISTANCE> PairType;

            assert(idx.size()==pos.size());
            const size_t num  = idx.size();
            if(num<=2) {
                for(size_t i=1;i<=num;++i) idx[i] = i;
                return;
            }
            CxxSeries<ItemType> items(num);
            CxxSeries<PairType> pairs((num*(num-1))>>1);

            // initialize all items
            for(size_t i=1;i<=num;++i)
                items << ItemType(i,pos[i]);
            std::cerr << "items=" << items << std::endl;

            size_t curr = 0;
            // pairs from current items
            {
                const size_t n = items.size();
                pairs.free();
                for(size_t i=1;i<=n;++i)
                {
                    for(size_t j=i+1;j<=n;++j)
                    {
                        pairs << PairType(proc,items[i],items[j]);
                    }
                }
                const PairType & pair = Sorting::Heap::Sort(pairs, PairType::Compare)[ Select(pairs.size()) ];
                std::cerr << "pair=" << pair << std::endl;
                idx[++curr] = pair.lhs.idx;
                idx[++curr] = pair.rhs.idx;
                RemoveItem(idx[1],items);
            }

        }

    };


    static inline double scalarDistance(const double a, const double b) noexcept
    {
        return fabs(a-b);
    }

}

#include "y/random/park-miller.hpp"

Y_UTEST(calculus_disperse)
{
    Random::ParkMiller ran;
    const size_t   n = 3;
    Vector<size_t> idx(n,0);
    Vector<double> pos(n,0);
    for(size_t i=n;i>0;--i)
    {
        pos[i] = ran.symm<double>();
    }

    std::cerr << "pos=" << pos << std::endl;

    Disperse::Make( TypeToType<double>(), idx,scalarDistance,pos);



}
Y_UDONE()

