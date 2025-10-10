//! \file

#ifndef Y_Fit_Variable_Included
#define Y_Fit_Variable_Included 1

#include "y/mkl/fit/entity.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Variable : public Entity
            {
            public:

            protected:
                template <typename UID> inline
                explicit Variable(const UID  & uid) :
                Entity(uid), indx(0)
                {
                }

            public:
                virtual ~Variable() noexcept;

                friend std::ostream & operator<<(std::ostream &, const Variable &);

                const size_t indx;
            private:
                Y_Disable_Copy_And_Assign(Variable);

            };



        }

    }

}

#endif // !Y_Fit_Variable_Included

