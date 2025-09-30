//! \file
#ifndef YACK_FUNCTOR_COMMAND_INCLUDED
#define YACK_FUNCTOR_COMMAND_INCLUDED 1

#include "y/functor/call.hpp"

namespace Yttrium {

    namespace Kernel {

        //______________________________________________________________________
        //
        //
        //! wrapper for host + method
        //
        //______________________________________________________________________
        template <
        typename R,
        typename TLIST,
        typename OBJECT_POINTER,
        typename METHOD_POINTER >
        class command : public virtual callable<R,TLIST>
        {
        public:
            //__________________________________________________________________
            //
            // types and definitions
            //__________________________________________________________________
            typedef callable<R,TLIST> callable_type; //!< alias
            Y_FUNCTOR_PARAMETERS();                  //!< parameters aliases

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! construct \param o object pointer \param m method pointer
            explicit command( const OBJECT_POINTER o, const METHOD_POINTER m ) :
            callable_type(),
            object_( o ),
            method_( m )
            {
                assert( NULL != object_ );
                assert( NULL != method_ );
            }
            //! destructor
            virtual ~command() noexcept {}

            //__________________________________________________________________
            //
            //! cloneable interface \return cloned command
            //__________________________________________________________________
            virtual  callable<R,TLIST> *clone() const { return new command( *this ); }

            //__________________________________________________________________
            //
            // calls
            //__________________________________________________________________

            //! no argument call \return call value
            inline R operator()(void)
            {
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )();
            }

            //! one argument call
            /**
             \param P1 param1
             \return call value
             */
            inline R operator()( param1 P1 )
            {
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )( P1 );
            }

            //! two arguments call
            /**
             \param P1 param1
             \param P2 param2
             \return call value
             */
            inline R operator()( param1 P1, param2 P2 )
            {
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )( P1, P2 );
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
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )( P1, P2, P3 );
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
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )( P1, P2, P3, P4);
            }

            //! five arguments call
            /**
             \param P1 param1
             \param P2 param2
             \param P3 param3
             \param P4 param3
             \param P5 param3
            \return call value
            */
            inline R operator()( param1 P1, param2 P2, param3 P3, param4 P4, param5 P5)
            {
                assert( NULL != object_ );
                assert( NULL != method_ );
                return ( (*object_).*method_ )( P1, P2, P3, P4, P5);
            }


        private:
            Y_Disable_Assign(command); //!< discarding

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4371)
#endif
            OBJECT_POINTER object_;    //!< object pointer
            METHOD_POINTER method_;    //!< method pointer

#if defined(_MSC_VER)
#pragma warning (pop)
#endif

            //! copy for the clone function \param other another command
            explicit command( const command &other ) noexcept:
            callable_type(),
            object_( other.object_ ),
            method_( other.method_ )
            {

            }
        };


    }

}

#endif

