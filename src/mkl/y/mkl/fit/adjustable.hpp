
//! \file

#ifndef Y_Fit_Adjustable_Included
#define Y_Fit_Adjustable_Included 1

#include "y/mkl/fit/entity.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class AdjustableCommon : public Entity
            {
            public:
                template <typename UID>
                inline explicit AdjustableCommon(const UID &uid) :
                Entity(uid)
                {
                }

                virtual ~AdjustableCommon() noexcept;

                virtual size_t count() const noexcept = 0;

            private:
                Y_Disable_Copy_And_Assign(AdjustableCommon);
            };

            template <typename ABSCISSA,typename ORDINATE>
            class Adjustable : public AdjustableCommon
            {
            public:
                template <typename UID>
                inline explicit Adjustable(const UID &uid) :
                AdjustableCommon(uid)
                {
                }


                inline virtual ~Adjustable() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(Adjustable);
            };


        }

    }

}

#endif // !Y_Fit_Adjustable_Included
