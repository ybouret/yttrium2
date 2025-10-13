
//! \file

#ifndef Y_Fit_Adjustable_Included
#define Y_Fit_Adjustable_Included 1

#include "y/mkl/fit/fwrapper.hpp"
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
                virtual size_t count() const noexcept = 0; //!< \return number of data points

            private:
                Y_Disable_Copy_And_Assign(AdjustableCommon); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            //
            //! Interface for Sample[s]
            //
            //
            //__________________________________________________________________
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
                typedef Cameo::Addition<ORDINATE> XAddition; //!< alias
                typedef Y_Fit_Function            Function;  //!< alias
                typedef Y_Fit_Gradient            Gradient;  //!< alias


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

                //! simple D2 evaluation
                /**
                 \param F    adjustable function
                 \param aorg current values
                 \return D2 at aorg w.r.t F
                 */
                virtual ORDINATE computeD2(Function &F, const Readable<ORDINATE> &aorg) = 0;

                //! simple D2 wrapper evaluation
                /**
                 \param func compatible function
                 \param aorg current parameters
                 \return D2 at aorg w.r.t F
                 */
                template <typename FUNC> inline
                ORDINATE computeD2_(FUNC &func, const Readable<ORDINATE> &aorg)
                {
                    FWrapper<FUNC,ABSCISSA,ORDINATE> F(func);
                    return computeD2(F,aorg);
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                ORDINATE  D2;     //!< last D2
                XAddition xadd;   //!< helper

            private:
                Y_Disable_Copy_And_Assign(Adjustable); //!< discarding

            };


        }

    }

}

#endif // !Y_Fit_Adjustable_Included
