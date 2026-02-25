
//! \file

#ifndef Y_Ink_Blur_Included
#define Y_Ink_Blur_Included 1

#include "y/ink/blur/hook.hpp"
#include "y/ink/ops.hpp"


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


        //______________________________________________________________________
        //
        //
        //
        //! Adapt blur call
        //
        //
        //______________________________________________________________________
        struct BlurFilter
        {

            //! apply compatible blur
            /**
             \param broker broker
             \param target target pixmap
             \param blur   compatible blur with Pixmap
             \param source source Pixmap
             */
            template <typename U, typename BLUR> static inline
            void Apply(Broker &broker, Pixmap<U> &target, BLUR &blur, const Pixmap<U> &source)
            {
                BlurProcess<U>::template Apply<BLUR>(broker,target,blur,source);
            }

        private:
            //__________________________________________________________________
            //
            //
            //
            //! transform Blur into object to use Ops::Transform
            //
            //
            //__________________________________________________________________
            template <typename U>
            struct BlurProcess
            {
                //! apply using Ops::Transform
                /**
                 \param broker  broker
                 \param target  target
                 \param blur    compatible blur  
                 \param source  source
                 */
                template <typename BLUR> static inline
                void Apply(Broker &broker, Pixmap<U> &target, BLUR &blur, const Pixmap<U> &source)
                {
                    App<BLUR> app(blur);
                    Ops::Transform(broker,target,app,source);
                }

            private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
                template <typename BLUR>
                class App
                {
                public:
                    inline explicit App(BLUR &_blur) noexcept : blur(_blur) {}
                    inline virtual ~App()            noexcept {}

                    inline void operator()(Pixmap<U>       & target,
                                           const Pixmap<U> & source,
                                           const Point       origin)
                    {
                        blur.apply(target,source,origin);
                    }

                private:
                    Y_Disable_Copy_And_Assign(App);
                    BLUR &blur;
                };
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)
            };
        };
    }

}

#endif // !Y_Ink_Blur_Included

