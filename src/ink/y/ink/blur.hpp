
//! \file

#ifndef Y_Ink_Blur_Included
#define Y_Ink_Blur_Included 1

#include "y/ink/blur/hook.hpp"


namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Blur Filter based and function
        //
        //
        //______________________________________________________________________
        template <typename T, template <typename> class FUNCTION>
        class Blur : public FUNCTION<T>, public BlurHook<T>
        {
        public:
            using FUNCTION<T>::blurFunction;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with no argument
            inline explicit Blur() : FUNCTION<T>(), BlurHook<T>( blurFunction() )
            {
            }

            //! setup \param arg1 first argument
            inline explicit Blur(const T arg1) : FUNCTION<T>(arg1), BlurHook<T>( blurFunction() )
            {
            }

            //! setup \param arg1 first argument \param arg2 second argument
            inline explicit Blur(const T arg1, const T arg2) : FUNCTION<T>(arg1,arg2), BlurHook<T>( blurFunction() )
            {
            }

            //! cleanup
            inline virtual ~Blur() noexcept {}


        private:
            Y_Disable_Copy_And_Assign(Blur); //!< discarding
        };

        

    }

}

#endif // !Y_Ink_Blur_Included

