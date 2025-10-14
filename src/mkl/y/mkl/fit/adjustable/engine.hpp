
//! \file

#ifndef Y_Fit_AdjustableEngine_Included
#define Y_Fit_AdjustableEngine_Included 1

#include "y/mkl/fit/adjustable/common.hpp"
#include "y/cameo/caddy.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            
            template <typename ORDINATE>
            class AdjustableEngine : public AdjustableCommon
            {
            public:
                typedef Cameo::Addition<ORDINATE> XAddition; //!< alias
                typedef Cameo::Caddy<ORDINATE>    CaddyType; //!< alias

                template <typename UID>
                explicit AdjustableEngine(const UID &uid) :
                AdjustableCommon(uid),
                D2(-1),
                xadd(),
                dFda(),
                cadd()
                {
                }
                

                virtual ~AdjustableEngine() noexcept {}


                ORDINATE         D2;   //!< current D2
                XAddition        xadd; //!< helper to compute D2
                Vector<ORDINATE> dFda; //!< store local gradient
                CaddyType        cadd; //!< dynamic additions

            private:
                Y_Disable_Copy_And_Assign(AdjustableEngine);

            };

        }
    }
}

#endif // !Y_Fit_AdjustableEngine_Included

