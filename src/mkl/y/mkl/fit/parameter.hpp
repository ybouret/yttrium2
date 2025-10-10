
//! \file

#ifndef Y_Fit_Parameter_Included
#define Y_Fit_Parameter_Included 1

#include "y/mkl/fit/entity.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Parameter : public Entity
            {
            public:
                typedef Keyed< String, ArcPtr<Parameter> > Pointer;

                template <typename UID> inline
                explicit Parameter(const UID  & uid) :
                Entity(uid), indx(0)
                {
                }


                virtual ~Parameter() noexcept;

                friend std::ostream & operator<<(std::ostream &, const Parameter &);
                
                const size_t indx;
            private:
                Y_Disable_Copy_And_Assign(Parameter);

            };



        }

    }

}

#endif // !Y_Fit_Parameter_Included

