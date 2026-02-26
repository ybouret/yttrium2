#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/cxx/series.hpp"
#include "y/sorting/heap.hpp"

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

        template <typename POSITION, typename DISTANCE, typename PROC> static inline
        void Make(TypeToType<DISTANCE>, Writable<size_t> &idx, PROC &proc, const Readable<POSITION> &pos)
        {
            assert(idx.size()==pos.size());
            const size_t n  = idx.size();
            if(n<=2) {
                for(size_t i=1;i<=n;++i) idx[i] = i;
                return;
            }

            const size_t np = (n*(n-1))>>1;

            // create items
            typedef Item<POSITION> ItemType;
            CxxSeries<ItemType>    items(n);
            for(size_t i=1;i<=n;++i)
            {
                items << ItemType(i,pos[i]);
            }
            std::cerr << "items=" << items << std::endl;

            // create pairs
            typedef Pair<POSITION,DISTANCE> PairType;
            CxxSeries<PairType> pairs(np);

            for(size_t i=1;i<=n;++i)
            {
                const ItemType &lhs = items[i];
                for(size_t j=i+1;j<=n;++j)
                {
                    pairs << PairType(proc,lhs,items[j]);
                }
            }
            std::cerr << "pairs=" << pairs << std::endl;
            Sorting::Heap::Sort(pairs,PairType::Compare);
            std::cerr << "pairs=" << pairs << std::endl;
            const PairType & pair = pairs[ Select(pairs.size()) ];
            std::cerr << "using " << pair << std::endl;
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

