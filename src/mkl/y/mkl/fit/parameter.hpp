
//! \file

#ifndef Y_Fit_Parameter_Included
#define Y_Fit_Parameter_Included 1

#include "y/mkl/fit/entity.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            //__________________________________________________________________
            //
            //
            //
            //! global parameter, shared between samples
            //
            //
            //__________________________________________________________________
            class Parameter : public Entity
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Keyed< String, ArcPtr<Parameter> > Pointer; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name \param idx global index
                template <typename UID> inline
                explicit Parameter(const UID  & uid,
                                   const size_t idx) :
                Entity(uid), indx(idx)
                {
                }

                //! cleanup
                virtual ~Parameter() noexcept;

                //! display
                friend std::ostream & operator<<(std::ostream &, const Parameter &);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t indx; //!< global index

            private:
                Y_Disable_Copy_And_Assign(Parameter); //!< discarding

            };



        }

    }

}

#endif // !Y_Fit_Parameter_Included

