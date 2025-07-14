//! \file
#ifndef YACK_FUNCTOR_CALLBACK_INCLUDED
#define YACK_FUNCTOR_CALLBACK_INCLUDED 1

#include "y/functor/call.hpp"

namespace Yttrium {

    namespace Kernel
    {

        //______________________________________________________________________
        //
        //! wrapper for a callable entity
        /**
         * this can be a C function or a functionoid
         *
         */
        //______________________________________________________________________
        template <typename R, typename TLIST, typename FUNCTION>
        class callback : public virtual callable<R,TLIST>
        {
        public:
            //__________________________________________________________________
            //
            // types and definitions
            //__________________________________________________________________
            typedef callable<R,TLIST> callable_type; //!< alias
            Y_FUNCTOR_PARAMETERS();                  //!< alias for parameters

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! constructor by copy of C-function or full functionoid \param fn functionoid
            explicit callback( const FUNCTION &fn ) : function_( fn ) {}

            //! destructor
            virtual ~callback() noexcept    {}

            //__________________________________________________________________
            //
            //! cloneable interface: use copy constructor
            //__________________________________________________________________

            //! \return cloned callback
            virtual callable<R,TLIST> *clone() const { return new callback( *this ); }

            //! no argument call \return call value
            inline R operator()(void)
            {
                return function_();
            }

            //! one argument call
            /**
             \param P1 param1
             \return call value
             */
            inline R operator()( param1 P1 )
            {
                return function_( P1 );
            }

            //! two arguments call
            /**
             \param P1 param1
             \param P2 param2
             \return call value
            */
            inline R operator()( param1 P1, param2 P2 )
            {
                return function_( P1, P2 );
            }

            //! three arguments call
            /**
             \param P1 param1
             \param P2 param2
             \param P3 param3
             \return call value
             */
            inline R operator()( param1 P1, param2 P2, param3 P3)
            {
                return function_( P1, P2, P3 );
            }

            //! four arguments call
            /**
             \param P1 param1
             \param P2 param2
             \param P3 param3
             \param P4 param4
             \return call value
             */
            inline R operator()( param1 P1, param2 P2, param3 P3, param4 P4)
            {
                return function_( P1, P2, P3, P4);
            }

            //! five arguments call
            /**
             \param P1 param1
             \param P2 param2
             \param P3 param3
             \param P4 param4
             \param P5 param5
             \return call value
             */
            inline R operator()( param1 P1, param2 P2, param3 P3, param4 P4, param5 P5)
            {
                return function_( P1, P2, P3, P4, P5);
            }


        private:
            Y_Disable_Assign(callback); //!< discarding

            //! use the copy semantics of FUNCTION to clone \param other another callback
            explicit callback( const callback &other ) : callable_type(), function_( other.function_ ) {}

            FUNCTION function_; //!< inner function
        };

    }

}

#endif

