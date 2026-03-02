
//! \file

#ifndef Y_Container_Algo_Disperse_Included
#define Y_Container_Algo_Disperse_Included 1

#include "y/container/cxx/series.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Algo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Dispersing by recursive median selection
        //
        //
        //______________________________________________________________________
        struct Disperse
        {
            static const char * const CallSign; //!< "Disperse"

            //__________________________________________________________________
            //
            //
            //
            //! item with given index and position
            //
            //
            //__________________________________________________________________
            template <typename POSITION>
            class Item
            {
            public:
                //! setup \param i index \param p position
                inline  Item(const size_t i, const POSITION &p) : idx(i), pos(p){}
                inline  Item(const Item &_) : idx(_.idx), pos(_.pos) {} //!< duplicate \param _ item
                inline ~Item() noexcept                              {} //!< cleanup

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Item &item)
                {
                    return os << '#' << item.idx << '@' << item.pos;
                }

                //! \param lhs pointer \param rhs pointer \return compared by index
                static inline
                SignType Compare(const Item * const lhs, const Item * const rhs) noexcept
                {
                    return Sign::Of(lhs->idx,rhs->idx);
                }

                const size_t   idx; //!< index
                const POSITION pos; //!< position

            private:
                Y_Disable_Assign(Item); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! pair with two (ordered by index) items and a distance
            //
            //
            //__________________________________________________________________
            template <
            typename POSITION,
            typename DISTANCE>
            class Pair
            {
            public:
                typedef Item<POSITION> ItemType; //!< alias

                //! setup
                /**
                 \param proc compute distance between two positions
                 \param lhsItem first item
                 \param rhsItem second item
                 */
                template <typename PROC>
                inline Pair(PROC &proc, const ItemType &lhsItem, const ItemType &rhsItem) :
                lhs( & lhsItem),
                rhs( & rhsItem),
                delta( proc(lhs->pos,rhs->pos) )
                {
                    if(lhs->idx>rhs->idx) CoerceSwap(lhs,rhs);
                    assert(lhs->idx<rhs->idx);
                }

                //! duplicate \param _ pait
                inline Pair(const Pair &_) : lhs(_.lhs), rhs(_.rhs), delta(_.delta) {}

                //! cleanup
                inline ~Pair() noexcept
                {
                }

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Pair &pair)
                {
                    return os << '|' << *pair.lhs << ':' << *pair.rhs << '|' << '=' << pair.delta;
                }

                //! \param lhs pair \param rhs pair \return compared by distance
                static inline
                SignType Compare(const Pair &lhs, const Pair &rhs)
                {
                    return Sign::Of(lhs.delta,rhs.delta);
                }

                //! \param lhs pair \param rhs pair \return compared by distance
                static inline
                SignType CompareAddr(const Pair * const lhs, const Pair * const rhs)
                {
                    return Compare(*lhs,*rhs);
                }

                //! \param idx index \return true iff idx matches lhs or rhs
                inline bool has(const size_t idx) const noexcept
                {
                    return idx==lhs->idx || idx==rhs->idx;
                }

                //! \param head index \return matching tail index
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


                const ItemType * const lhs;   //!< first item
                const ItemType * const rhs;   //!< second item
                const DISTANCE         delta; //!< distance

            private:
                Y_Disable_Assign(Pair); //!< discarding
            };

            template <typename DISTANCE> struct With
            {
                template <typename POSITION,typename PROC> static inline
                void Make(Writable<size_t> &idx, PROC &proc, const Readable<POSITION> &pos)
                {
                    typedef Item<POSITION>          ItemType;
                    typedef Pair<POSITION,DISTANCE> PairType;
                    assert(idx.size()==pos.size());

                    //--------------------------------------------------------------
                    //
                    // check cases
                    //
                    //--------------------------------------------------------------
                    const size_t num  = idx.size();
                    if(num<=2) {
                        for(size_t i=1;i<=num;++i) idx[i] = i;
                        return;
                    }

                    //--------------------------------------------------------------
                    //
                    // initialize all items
                    //
                    //--------------------------------------------------------------
                    CxxSeries<ItemType>   items(num);
                    for(size_t i=1;i<=num;++i)
                        items << ItemType(i,pos[i]);

                    //--------------------------------------------------------------
                    //
                    // initialize all pairs
                    //
                    //--------------------------------------------------------------
                    CxxSeries<PairType>   pairs((num*(num-1))>>1);
                    for(size_t i=1;i<=num;++i)
                        for(size_t j=i+1;j<=num;++j)
                            pairs << PairType(proc,items[i],items[j]);




                    //--------------------------------------------------------------
                    //
                    // find first pair and first two items
                    //
                    //--------------------------------------------------------------
                    size_t curr = 0;
                    {
                        const PairType &pair = Sorting::Heap::Sort(pairs,PairType::Compare)[ Select(pairs) ];
                        //std::cerr << "selected pair=" << pair << std::endl;
                        const size_t head = idx[++curr] = pair.lhs->idx;
                        /* tail */          idx[++curr] = pair.rhs->idx;
                        //std::cerr << "starting with " << idx[1] << " -> " << idx[2] << " : $" << pair.delta << std::endl;
                        NoPairWith(head,pairs);
                    }
                    assert(2==curr);


                    CxxSeries<PairType *> handle(num);
                    for(;curr<num;)
                    {
                        const size_t head = idx[curr];
                        handle.free();
                        for(size_t i=pairs.size();i>0;--i)
                        {
                            PairType &pair = pairs[i];
                            if(!pair.has(head)) continue;
                            handle << &pair;
                        }
                        assert(handle.size()>0);
                        const PairType &pair = *Sorting::Heap::Sort(handle,PairType::CompareAddr)[ Select(handle) ];
                        const size_t    tail = pair.tailMatching(head);
                        //std::cerr << "next   = " << head << " -> " << tail << " : $" << pair.delta << std::endl;
                        idx[++curr] = tail;
                        NoPairWith(head,pairs);
                    }
                }

            };

        private:

            //! \param arr SORTED array \return median index
            template <typename ARR> static inline
            size_t Select(const ARR &arr) noexcept
            {
                const size_t n = arr.size();
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


            //! remove pairs having idx \param idx index \param pairs series of pairs
            template <typename PAIR> static inline
            void NoPairWith(const size_t idx, CxxSeries<PAIR> &pairs)
            {
                for(size_t i=1;i<=pairs.size();)
                {
                    PAIR &pair = pairs[i];
                    if(pair.has(idx)) {
                        Memory::Stealth::Swap(pair,pairs.tail());
                        pairs.pop();
                    }
                    else
                        ++i;

                }
            }

        };

    }

}

#endif // !Y_Container_Algo_Disperse_Included
