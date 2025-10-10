

//! \file

#ifndef Y_Fit_Indexed_Included
#define Y_Fit_Indexed_Included 1

#include "y/mkl/fit/entity.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            enum Level
            {
                PrimaryLevel,
                WorkingLevel
            };

            //__________________________________________________________________
            //
            //
            //
            //! indexed entity
            //
            //
            //__________________________________________________________________
            class Indexed : public Entity
            {
            public:
                static const unsigned Levels = WorkingLevel+1;

                template <typename UID> inline
                explicit Indexed(const UID &  uid,
                                 const size_t primaryIndex) :
                Entity(uid), indx()
                {
                    setup(primaryIndex);
                }

                virtual ~Indexed() noexcept;

                const size_t indx[Levels];
            private:
                Y_Disable_Copy_And_Assign(Indexed);
                void setup(const size_t) noexcept;
            };

        }

    }

}

#endif // !Y_Fit_Indexed_Included

