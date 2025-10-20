
//! \file

#ifndef Y_Fit_AdjustableCommon_Included
#define Y_Fit_AdjustableCommon_Included 1

#include "y/mkl/fit/type/fwrapper.hpp"
#include "y/cameo/addition.hpp"

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
            //! Common parts for Adjustable
            //
            //
            //__________________________________________________________________
            class AdjustableCommon : public Entity
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name
                template <typename UID>
                inline explicit AdjustableCommon(const UID &uid) :
                Entity(uid)
                {
                }

                virtual ~AdjustableCommon() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t count()                            const noexcept = 0; //!< \return number of data points
                virtual size_t active(const Readable<bool> &used) const noexcept = 0;
                
            private:
                Y_Disable_Copy_And_Assign(AdjustableCommon); //!< discarding
            };

        }

    }

}

#endif // !Y_Fit_AdjustableCommon_Included

