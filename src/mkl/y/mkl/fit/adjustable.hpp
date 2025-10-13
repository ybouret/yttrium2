
//! \file

#ifndef Y_Fit_Adjustable_Included
#define Y_Fit_Adjustable_Included 1

#include "y/mkl/fit/variables.hpp"
#include "y/functor.hpp"
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
                virtual size_t count() const noexcept = 0;

            private:
                Y_Disable_Copy_And_Assign(AdjustableCommon); //!< discarding
            };


#define Y_Fit_Ret_Type ORDINATE
#define Y_Fit_Fcn_Args TL4(Readable<ABSCISSA>,size_t,Variables,Readable<ORDINATE>)
#define Y_Fit_Functor  Functor<Y_Fit_Ret_Type,Y_Fit_Fcn_Args>
            template <typename ABSCISSA,typename ORDINATE>
            class Adjustable : public AdjustableCommon
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Cameo::Addition<ORDINATE> XAddition;
                typedef Y_Fit_Functor             Function;


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name
                template <typename UID>
                inline explicit Adjustable(const UID &uid) :
                AdjustableCommon(uid), D2(-1), xadd()
                {
                }


                //! cleanup
                inline virtual ~Adjustable() noexcept {}


                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual ABSCISSA computeD2(Function &F, const Readable<ORDINATE> &aorg) = 0;


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                ORDINATE  D2;
                XAddition xadd;
            private:
                Y_Disable_Copy_And_Assign(Adjustable); //!< discarding

            };


        }

    }

}

#endif // !Y_Fit_Adjustable_Included
