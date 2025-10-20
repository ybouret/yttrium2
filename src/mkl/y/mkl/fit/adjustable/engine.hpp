
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

            //__________________________________________________________________
            //
            //
            //
            //! Ordinate only data to collect
            //
            //
            //__________________________________________________________________
            template <typename ORDINATE>
            class AdjustableEngine : public AdjustableCommon
            {
            public:
                typedef Cameo::Addition<ORDINATE> XAddition; //!< alias
                typedef Cameo::Caddy<ORDINATE>    CaddyType; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name
                template <typename UID>
                explicit AdjustableEngine(const UID &uid) :
                AdjustableCommon(uid),
                D2(-1),
                xadd(),
                dFda(),
                beta(),
                alpha(),
                cadd()
                {
                }
                
                //! cleanup
                virtual ~AdjustableEngine() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! scatter local values into global values
                /**
                 \param a_global global array
                 \param a_local  local array
                 */
                virtual void scatter(Writable<ORDINATE>       &a_global,
                                     const Readable<ORDINATE> &a_local) const noexcept = 0;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! symmetrize alpha
                void symmetrize() noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                ORDINATE         D2;    //!< current D2
                XAddition        xadd;  //!< helper to compute D2
                Vector<ORDINATE> dFda;  //!< store local gradient
                Vector<ORDINATE> beta;  //!< local D2 gradient
                Matrix<ORDINATE> alpha; //!< local D2 curvature
                CaddyType        cadd;  //!< dynamic additions
                
            private:
                Y_Disable_Copy_And_Assign(AdjustableEngine); //!< discarding
            };

        }
    }
}

#endif // !Y_Fit_AdjustableEngine_Included

