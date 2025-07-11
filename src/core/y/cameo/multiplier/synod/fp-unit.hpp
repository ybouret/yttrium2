

//! \file

#ifndef Y_Cameo_Multipler_FP_Unit_Included
#define Y_Cameo_Multipler_FP_Unit_Included 1

#include "y/cameo/multiplier/synod/fp-mass.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Synod
        {
            template <typename T>
            class FPUnit
            {
            public:
                typedef Protean::WarpedCacheOf<FPUnit,SingleThreadedClass> Cache;
                typedef const T & ParamType;

                inline FPUnit(const T &value) noexcept :
                data(value),
                mass( GetFPointMass(data) ),
                next(0),
                prev(0)
                {
                }

                inline ~FPUnit() noexcept
                {
                }

                inline const FPUnit & operator*() const noexcept { return *this; }

                inline friend std::ostream & operator<< (std::ostream &os, const FPUnit &self)
                {
                    return os << self.data;
                }

                static inline SignType Compare(const FPUnit * const lhs,
                                               const FPUnit * const rhs) noexcept
                {
                    return Sign::Of(lhs->mass,rhs->mass);
                }

                const T   data;
                const int mass;
                FPUnit *  next;
                FPUnit *  prev;
            private:
                Y_Disable_Copy_And_Assign(FPUnit);
            };

            

        }

    }

}

#endif

