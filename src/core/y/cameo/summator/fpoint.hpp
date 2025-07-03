
//! \file

#ifndef Y_Cameo_FPointSummator_Included
#define Y_Cameo_FPointSummator_Included 1

#include "y/cameo/summator.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/sign.hpp"
#include "y/container/ordered/priority-queue.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        template <typename T>
        class FPointSummator : public Summator<T>
        {
        public:
            Y_Args_Declare(T,Type);
            typedef typename MKL::ScalarFor<MutableType>::Type ScalarType;
            typedef const ScalarType RankType;

            class Unit
            {
            public:
                inline  Unit(ParamType x) : data(x), rank( MKL::Fabs<T>::Of(data) ) {}
                inline  Unit(const Unit &other) : data(other.data), rank(other,rank) {}
                inline ~Unit() noexcept {}

                struct Comparator {
                    inline SignType operator()(const Unit &lhs, const Unit &rhs) {
                        return Sign::Of(lhs.rank,rhs.rank);
                    }
                };

                ConstType data;
                RankType  rank;
                Y_Disable_Assign(Unit);
            };

            typedef PriorityQueue<Unit,typename Unit::Comparator> Accumulator;

            virtual void ldz() noexcept { acc.free(); }

        private:
            Y_Disable_Copy_And_Assign(FPointSummator);
            Accumulator acc;
        };


    }

}

#endif

