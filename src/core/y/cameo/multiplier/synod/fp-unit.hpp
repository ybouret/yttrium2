

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
            //__________________________________________________________________
            //
            //
            //
            //! holds data and its mass within a list
            //
            //
            //__________________________________________________________________
            template <typename T>
            class FPUnit
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Protean::WarpedCacheOf<FPUnit,SingleThreadedClass> Cache;     //!< alias
                typedef const T &                                          ParamType; //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param value copied and computed mass
                inline FPUnit(const T &value) noexcept :
                data(value),
                mass( GetFPointMass(data) ),
                next(0),
                prev(0)
                {
                }

                //! cleanup
                inline ~FPUnit() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! access to print list \return *this
                inline const FPUnit & operator*() const noexcept { return *this; }

                //! \param os output stream \param self *this \return os
                inline friend std::ostream & operator<< (std::ostream &os, const FPUnit &self)
                {
                    return os << self.data;
                }

                //! \param lhs lhs \param rhs rhs \return mass comparison
                static inline SignType Compare(const FPUnit * const lhs,
                                               const FPUnit * const rhs) noexcept
                {
                    assert(lhs); assert(rhs);
                    return Sign::Of(lhs->mass,rhs->mass);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T   data; //!< value
                const int mass; //!< associated exponent
                FPUnit *  next; //!< for list
                FPUnit *  prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(FPUnit); //!< discarding
            };

            

        }

    }

}

#endif

