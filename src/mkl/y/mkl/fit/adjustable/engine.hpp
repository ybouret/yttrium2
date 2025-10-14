
//! \file

#ifndef Y_Fit_AdjustableEngine_Included
#define Y_Fit_AdjustableEngine_Included 1

#include "y/mkl/fit/adjustable/common.hpp"
#include "y/cameo/caddy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/matrix.hpp"

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
                beta(),
                cadd()
                {
                }
                

                virtual ~AdjustableEngine() noexcept {}


                void symmetrize() noexcept
                {
                    const size_t nvar = alpha.rows;
                    for(size_t i=1;i<=nvar;++i)
                    {
                        for(size_t j=1;j<i;++j) alpha[i][j] = alpha[j][i];
                    }
                }

                ORDINATE         D2;    //!< current D2
                XAddition        xadd;  //!< helper to compute D2
                Vector<ORDINATE> dFda;  //!< store local gradient
                Vector<ORDINATE> beta;  //!< local D2 gradient
                Matrix<ORDINATE> alpha; //!< local D2 curvature
                CaddyType        cadd;  //!< dynamic additions

            private:
                Y_Disable_Copy_And_Assign(AdjustableEngine);

            };

        }
    }
}

#endif // !Y_Fit_AdjustableEngine_Included

