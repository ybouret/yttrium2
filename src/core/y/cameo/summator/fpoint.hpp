
//! \file

#ifndef Y_Cameo_FPointSummator_Included
#define Y_Cameo_FPointSummator_Included 1

#include "y/cameo/summator/api.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/sign.hpp"
#include "y/container/ordered/priority-queue.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Floating Point Summator using priority queue
        //
        //
        //______________________________________________________________________
        template <typename T>
        class FPointSummator : public Summator<T>, public Ingress< PriorityQueuePolicy >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type);                                         //!< aliases
            typedef Ingress<PriorityQueuePolicy>               IngressType; //!< alias
            typedef typename MKL::ScalarFor<MutableType>::Type ScalarType;  //!< alias
            typedef const ScalarType                           RankType;    //!< alias

            //__________________________________________________________________
            //
            //
            //! Internal Unit to insert into priority queue
            //
            //__________________________________________________________________
            class Unit
            {
            public:
                //______________________________________________________________
                //
                //! Comparator
                //______________________________________________________________
                struct Comparator {

                    //! compare units
                    /**
                     \param lhs first arg
                     \param rhs second arg
                     \return decreasing comparison
                     */
                    inline SignType operator()(const Unit &lhs, const Unit &rhs) {
                        return Sign::Of(rhs.rank,lhs.rank);
                    }
                };

                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                //! setup \param x value
                inline  Unit(ParamType x)       : data(x),          rank( MKL::Fabs<T>::Of(data) ) {}

                //! duplicate \param other antoher unit
                inline  Unit(const Unit &other) : data(other.data), rank(other.rank) {}

                //! cleanup
                inline ~Unit() noexcept {}

                //! display \param os output stream \param self *this \return os
                inline friend std::ostream & operator<<(std::ostream &os, const Unit &self)
                {
                    return os << self.data;
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                ConstType data; //!< original data
                RankType  rank; //!< data rank

            private:
                Y_Disable_Assign(Unit); //!< discarding
            };

            typedef PriorityQueue<Unit,typename Unit::Comparator> Accumulator; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param minimalCapacity optional reserved memory
            inline explicit FPointSummator(const size_t minimalCapacity=0) :
            Summator<T>(),
            IngressType(),
            acc(WithAtLeast,minimalCapacity)
            {
            }

            //! cleanup
            inline virtual ~FPointSummator() noexcept
            {
            }


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void     ldz() noexcept { acc.free(); }

            inline virtual T sum()
            {
                if( acc.size() <= 0 )
                    return T(0);
                
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
            Y_Disable_Copy_And_Assign(FPointSummator); //!< discarding
            Accumulator acc; //!< inner accumulator

            inline virtual const PriorityQueuePolicy & locus() const noexcept { return acc; }

            inline virtual void add(ParamType x)
            {
                acc.push(x);
                std::cerr << acc.peek() << " @" << acc << std::endl;
            }

        };


    }

}

#endif

