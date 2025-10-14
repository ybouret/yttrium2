//! \file

#ifndef Y_Fit_Variable_Included
#define Y_Fit_Variable_Included 1

#include "y/mkl/fit/parameter.hpp"

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
            //! Local variable
            //
            //
            //__________________________________________________________________
            class Variable : public Parameter
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Keyed< String, ArcPtr<Variable> > Pointer; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param uid name
                 \param idx local index
                 \param prm global parameter
                 */
                template <typename UID> inline
                explicit Variable(const UID  &     uid,
                                  const size_t     idx,
                                  const Parameter &prm) :
                Parameter(uid,idx),
                global(prm)
                {
                }

                //! cleanup
                virtual ~Variable() noexcept;

                //! display
                friend std::ostream & operator<<(std::ostream &, const Variable &);


                

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Parameter &global; //!< global parameter

            private:
                Y_Disable_Copy_And_Assign(Variable); //!< discarding

            };



        }

    }

}

#endif // !Y_Fit_Variable_Included

