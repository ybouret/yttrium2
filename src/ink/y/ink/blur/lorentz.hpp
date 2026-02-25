
//! \file

#ifndef Y_Ink_Blur_Lorentz_Included
#define Y_Ink_Blur_Lorentz_Included 1

#include "y/ink/blur/function.hpp"


namespace Yttrium
{
    namespace Ink
    {
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
        class LorentzBlurCommon
        {
        public:
            static const char * const CallSign;
            explicit LorentzBlurCommon() noexcept;
            virtual ~LorentzBlurCommon() noexcept;

        private:
            Y_Disable_Copy_And_Assign(LorentzBlurCommon);
        };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        //______________________________________________________________________
        //
        //
        //
        //! Lorentz Blur Function
        //
        //
        //______________________________________________________________________
        template <typename T>
        class LorentzBlur : public LorentzBlurCommon, public BlurFunction<T>
        {
        public:
            using BlurFunction<T>::one;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param scaling parameter
            inline explicit LorentzBlur(const T scaling) :
            sig( scaling ),
            sig2( sig*sig )
            {

            }

            //! cleanup
            inline virtual ~LorentzBlur() noexcept {}

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual const char * callSign() const noexcept { return CallSign; }

            inline virtual T operator()(const unit_t r2) const
            {
                const T u2  = (T)r2;
                const T arg = u2 / sig2;
                return one/(one+arg);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const T sig;    //!< scaling
            const T sig2;   //!< sig^2

        private:
            Y_Disable_Copy_And_Assign(LorentzBlur); //!< discarding
        };
    }

}

#endif // !Y_Ink_Blur_Lorentz_Included

