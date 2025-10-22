//! \file

#ifndef Y_MKL_Fit_Assembly_Included
#define Y_MKL_Fit_Assembly_Included 1

#include "y/mkl/fit/type/entity.hpp"

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
            //! interface to display assembly of entities
            //
            //
            //__________________________________________________________________
            class Assembly
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                explicit Assembly() noexcept; //!< setup

            public:
                virtual ~Assembly() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
            protected:
                void admit(const Entity &) noexcept; //!< register
            public:

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t maxNameSize; //!< max name size

            private:
                Y_Disable_Copy_And_Assign(Assembly); //!< discarding
            };

        }
    }

}

#endif // !Y_MKL_Fit_Assembly_Included

