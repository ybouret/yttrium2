//! \file

#ifndef  Y_MKL_Intervals_Included
#define  Y_MKL_Intervals_Included 1

#include "y/mkl/interval.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace MKL
    {
        //______________________________________________________________________
        //
        //
        //
        //! Intervals
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Intervals : public CxxArray< Interval<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Interval<T>              IntervalType; //!< alias
            typedef CxxArray<IntervalType >  AssemblyType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Intervals(const size_t dims) : AssemblyType(dims) {} //!< initialize to R^dims \param dims dimensions
            inline virtual ~Intervals() noexcept                              {} //!< cleanup

            //! duplicate \param other another set of intervals
            inline Intervals(const Intervals &other) :
            Container(),
            AssemblyType(other)
            {}

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const Intervals &domain)
            {
                os << '{';
                const size_t n = domain.size();
                if(n>0)
                {
                    os << domain[1];
                    for(size_t i=2;i<=n;++i)
                        os << " x " << domain[i];
                }
                os << '}';
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! test each coordinate is in corresponding interval
            /**
             \param arr array in R^size
             \return true iff vector is contained
             */
            template <typename ARRAY> inline
            bool contains(ARRAY &arr) const noexcept
            {
                const Readable<IntervalType> &self = *this;
                assert(self.size() == arr.size() );
                for(size_t i=self.size();i>0;--i)
                {
                    if(!self[i].contains(arr[i])) return false;
                }
                return true;
            }


        private:
            Y_Disable_Assign(Intervals); //!< discarding
        };
    }
}

#endif

