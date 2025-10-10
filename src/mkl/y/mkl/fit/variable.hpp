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

            class Variable : public Parameter
            {
            public:
                typedef Keyed< String, ArcPtr<Variable> > Pointer;

                template <typename UID> inline
                explicit Variable(const UID  &     uid,
                                  const size_t     idx,
                                  const Parameter &prm) :
                Parameter(uid,idx),
                parameter(prm)
                {
                }

                virtual ~Variable() noexcept;

                friend std::ostream & operator<<(std::ostream &, const Variable &);

                const Parameter &parameter;

            private:
                Y_Disable_Copy_And_Assign(Variable);

            };



        }

    }

}

#endif // !Y_Fit_Variable_Included

