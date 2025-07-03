
//! \file

#ifndef Y_Cameo_FPointSummator_Included
#define Y_Cameo_FPointSummator_Included 1

#include "y/cameo/summator.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/sign.hpp"
#include "y/container/ordered/priority-queue.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        template <typename T>
        class FPointSummator : public Summator<T>, public Ingress< PriorityQueuePolicy >
        {
        public:
            Y_Args_Declare(T,Type);
            typedef Ingress<PriorityQueuePolicy>               IngressType;
            typedef typename MKL::ScalarFor<MutableType>::Type ScalarType;
            typedef const ScalarType                           RankType;

            class Unit
            {
            public:
                inline  Unit(ParamType x)       : data(x),          rank( MKL::Fabs<T>::Of(data) ) {}
                inline  Unit(const Unit &other) : data(other.data), rank(other.rank) {}
                inline ~Unit() noexcept {}

                struct Comparator {
                    inline SignType operator()(const Unit &lhs, const Unit &rhs) {
                        return Sign::Of(rhs.rank,lhs.rank);
                    }
                };

                inline friend std::ostream & operator<<(std::ostream &os, const Unit &self)
                {
                    return os << self.data;
                }

                ConstType data;
                RankType  rank;
                Y_Disable_Assign(Unit);
            };

            typedef PriorityQueue<Unit,typename Unit::Comparator> Accumulator;

            inline explicit FPointSummator(const size_t minimalCapacity=0) :
            Summator<T>(),
            IngressType(),
            acc(WithAtLeast,minimalCapacity)
            {
            }

            inline virtual ~FPointSummator() noexcept
            {
            }



            virtual void ldz() noexcept { acc.free(); }

            inline virtual T sum()
            {
                if( acc.size() <= 0 ) return 0;
                while(acc.size()>1)
                {
                    const Unit lhs = acc.pop();
                    const Unit rhs = acc.pop();
                    ConstType  tmp = lhs.data + rhs.data;
                    add(tmp);
                }
                assert(1==acc.size());
                ConstType result = acc.pop().data;
                assert(0==acc.size());
                return result;
            }

        private:
            Y_Disable_Copy_And_Assign(FPointSummator);
            Accumulator acc;

            inline virtual const PriorityQueuePolicy & locus() const noexcept { return acc; }

            inline virtual void add(ConstType & x)
            {
                acc.push(x);
                std::cerr << acc.peek() << " @" << acc << std::endl;
            }

        };


    }

}

#endif

