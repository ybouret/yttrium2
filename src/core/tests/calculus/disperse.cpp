#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/container/cxx/series.hpp"
#include "y/sorting/heap.hpp"
#include "y/core/utils.hpp"
#include "y/exception.hpp"

#include <cmath>

using namespace Yttrium;

namespace Yttrium
{
    struct Disperse
    {
        static const char * const CallSign;

        //! item with given index and position
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

            static inline
            SignType Compare(const Item * const lhs, const Item * const rhs) noexcept
            {
                return Sign::Of(lhs->idx,rhs->idx);
            }

            const size_t   idx;
            const POSITION pos;

        private:
            Y_Disable_Assign(Item);
        };

        //! pair with two (ordered by index) items and a distance
        template <
        typename POSITION,
        typename DISTANCE>
        class Pair
        {
        public:
            typedef Item<POSITION> ItemType;

            template <typename PROC>
            inline Pair(PROC &proc, const ItemType &lhsItem, const ItemType &rhsItem) :
            lhs( & lhsItem),
            rhs( & rhsItem),
            delta( proc(lhs->pos,rhs->pos) )
            {
                if(lhs->idx>rhs->idx) CoerceSwap(lhs,rhs);
                assert(lhs->idx<rhs->idx);
            }

            inline Pair(const Pair &_) : lhs(_.lhs), rhs(_.rhs), delta(_.delta) {}


            inline ~Pair() noexcept
            {
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Pair &pair)
            {
                return os << '|' << *pair.lhs << ':' << *pair.rhs << '|' << '=' << pair.delta;
            }

            static inline
            SignType Compare(const Pair &lhs, const Pair &rhs)
            {
                return Sign::Of(lhs.delta,rhs.delta);
            }

            static inline
            SignType CompareAddr(const Pair * const lhs, const Pair * const rhs)
            {
                return Compare(*lhs,*rhs);
            }

            inline bool has(const size_t idx) const noexcept
            {
                return idx==lhs->idx || idx==rhs->idx;
            }

            inline size_t tailMatching(const size_t head) const noexcept
            {
                assert( has(head) );
                if(head == lhs->idx)
                {
                    return rhs->idx;
                }
                else
                {
                    assert(head==rhs->idx);
                    return lhs->idx;
                }
            }


            const ItemType * const lhs;
            const ItemType * const rhs;
            const DISTANCE         delta;

        private:
            Y_Disable_Assign(Pair);
        };


        //! select the median index
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
        void RemoveItem(const size_t idx, CxxSeries<ITEM *> &iAddr)
        {
            assert(iAddr.size()>0);
            const size_t count = iAddr.size();
            for(size_t i=count;i>0;--i)
            {
                ITEM &item = *iAddr[i];
                if(idx == item.idx)
                {
                    std::cerr << "Remove Found " << item << std::endl;
                    Swap(iAddr[i],iAddr[count]);
                    iAddr.pop();
                    return;
                }
            }
            throw Specific::Exception(CallSign,"missing RemoveItem(%u)", (unsigned)idx);
        }

        template <typename PAIR> static inline
        void NoPairWith(const size_t idx, CxxSeries<PAIR> &pairs)
        {
            std::cerr << "removing pairs with #" << idx << std::endl;
            for(size_t i=1;i<=pairs.size();)
            {
                PAIR &pair = pairs[i];
                if(pair.has(idx))
                {
                    std::cerr << "\tfound bad " << pair << std::endl;
                    Memory::Stealth::Swap(pair,pairs.tail());
                    pairs.pop();
                }
                else
                {
                    ++i;
                }
            }
        }

        template <typename ITEM> static inline
        void SetLeading(const size_t idx, CxxSeries<ITEM *> &iAddr)
        {
            assert(iAddr.size()>0);
            const size_t count = Sorting::Heap::Sort(iAddr,ITEM::Compare).size();
            for(size_t i=count;i>0;--i)
            {
                ITEM &item = *iAddr[i];
                if(idx == item.idx)
                {
                    std::cerr << "Found " << item << std::endl;
                    Swap(iAddr[i],iAddr[1]);
                    return;
                }
            }
            throw Specific::Exception(CallSign,"missing SetLeading(%u)", (unsigned)idx);
        }

        template <typename POSITION, typename DISTANCE, typename PROC> static inline
        void Make(TypeToType<DISTANCE>, Writable<size_t> &idx, PROC &proc, const Readable<POSITION> &pos)
        {
            typedef Item<POSITION>          ItemType;
            typedef Pair<POSITION,DISTANCE> PairType;
            assert(idx.size()==pos.size());

            // check cases
            const size_t num  = idx.size();
            if(num<=2) {
                for(size_t i=1;i<=num;++i) idx[i] = i;
                return;
            }




            // initialize all items
            CxxSeries<ItemType>   items(num);
            for(size_t i=1;i<=num;++i)
                items << ItemType(i,pos[i]);
            std::cerr << "initial items=" << items << std::endl;

            // initialize all pairs
            CxxSeries<PairType>   pairs((num*(num-1))>>1);
            for(size_t i=1;i<=num;++i)
                for(size_t j=i+1;j<=num;++j)
                    pairs << PairType(proc,items[i],items[j]);
            std::cerr << "initial pairs=" << pairs << std::endl;


            // find first pair and first two items
            size_t curr = 0;
            {
                const PairType &pair = Sorting::Heap::Sort(pairs,PairType::Compare)[ Select(pairs.size()) ];
                std::cerr << "selected pair=" << pair << std::endl;
                const size_t head = idx[++curr] = pair.lhs->idx;
                idx[++curr] = pair.rhs->idx;
                NoPairWith(head,pairs);
                std::cerr << "remaining = " << pairs << std::endl;
                std::cerr << "starting with " << idx[1] << " -> " << idx[2] << std::endl;
            }
            assert(2==curr);


            CxxSeries<PairType *> handle(num);
            {
                const size_t head = idx[curr];
                std::cerr << "new head = " << head << std::endl;
                handle.free();
                for(size_t i=pairs.size();i>0;--i)
                {
                    PairType &pair = pairs[i];
                    if(!pair.has(head)) continue;
                    std::cerr << "\tusing " << pair << std::endl;
                    handle << &pair;
                }
                const PairType &pair = *Sorting::Heap::Sort(handle,PairType::CompareAddr)[ Select(handle.size()) ];
                std::cerr << "choice = " << pair << std::endl;
                const size_t    tail = pair.tailMatching(head);
                std::cerr << "tail   = " << tail << std::endl;
            }

#if 0
            size_t                hmax = 0;
            for(;curr<num;++curr)
            {
                const size_t hook = idx[curr];
                std::cerr << "hook is now #" << hook << std::endl;
                handle.free();
                for(size_t i=pairs.size();i>0;--i)
                {
                    PairType &pair = pairs[i];
                    if(!pair.has(hook)) continue;
                    std::cerr << "using " << pair << std::endl;
                    handle << &pair;
                    InSituMax(hmax,handle.size());
                }
                assert(handle.size()>0);
                const PairType &pair = *Sorting::Heap::Sort(handle,PairType::CompareAddr)[ Select(handle.size()) ];
                std::cerr << "choice=" << pair << std::endl;
                assert(pair.has(hook));
                const size_t tail = (pair.lhs->idx == hook)  ? pair.rhs->idx : pair.lhs->idx;
                std::cerr << "tail will be " << tail << std::endl;
                idx[++curr] = tail;
                NoPairWith(hook,pairs);
                std::cerr << "remaining = " << pairs << std::endl;
                std::cerr << "curr = " << curr << std::endl;
            }
            std::cerr << "hmax=" << hmax << std::endl;
#endif



        }

    };

    const char * const Disperse:: CallSign = "Disperse";

    static inline double scalarDistance(const double a, const double b) noexcept
    {
        return fabs(a-b);
    }

}

#include "y/random/park-miller.hpp"
#include "y/ascii/convert.hpp"

Y_UTEST(calculus_disperse)
{
    Random::ParkMiller ran;
    const size_t   n = argc>1 ? ASCII::Convert::To<size_t>(argv[1]) : 3;
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

