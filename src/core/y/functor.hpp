//! \file
#ifndef Y_FUNCTOR_INCLUDED
#define Y_FUNCTOR_INCLUDED 1


#include "y/functor/callback.hpp"
#include "y/functor/command.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //! Functor
    /**
     - R     is the return type
     - TLIST is the parameters type list
     */
    //__________________________________________________________________________
    template <typename R, class TLIST>
    class Functor : public Kernel::callable<R,TLIST>
    {
    public:
        //______________________________________________________________________
        //
        // types and definitions
        //______________________________________________________________________
        typedef R                                   result;    //!< alias for result
        typedef TLIST                               arguments; //!< alias for type list
        typedef typename Kernel::callable<R,TLIST>  callable;  //!< base class
        Y_FUNCTOR_PARAMETERS();                                //!< alias for parameters


        //______________________________________________________________________
        //
        // C++
        //______________________________________________________________________

        //! destroy the internal wrappers
        inline virtual ~Functor() noexcept { assert(function_); destroy(); }


        //! copy: duplicate the functor context \param other another functor
        inline Functor( const Functor &other ) :
        callable(), function_( other.function_->clone() )
        { assert( function_ ); }

        //! assign: duplicate source context
        /**
         \param other another functor
         \return *this
         */
        inline Functor & operator=( const Functor &other )
        {
            if( this != &other )
            {
                //-- unsafe --
                callable *fn = other.function_->clone(); assert(fn);
                //--  safe  --
                destroy();
                function_ = fn;
            }
            return *this;
        }

        //! functionoid constructor
        /**
         \param functionoid a callable object
         functionoid can be of TWO types
         - it can be a regular C function, whose arguments and return types are compatible
         with the functor prototype.
         - it can be a full C++ object with an operator()(...)  whose arguments and return types are compatible
         with the functor prototype. In that case, THE C++ OBJECT IS COPIED, i.e. the whole
         context is wrapped in that functor.

         This is achieved through the kernel::callback which uses the copy semantic of FUNCTION.
         */
        template <typename FUNCTION>
        inline Functor( const FUNCTION &functionoid ) : callable(),
        function_( new Kernel::callback<R,TLIST,FUNCTION>(functionoid) ) {}

        //! object+method constructor
        /**
         \param o an object pointer
         \param m an object method, like &OBJECT_POINTER::DoSomething(...)
         Since only the pointer is copied, this strategy can be used
         for building one functor whose context can be changed by tweaking the
         original object.
         */
        template <typename OBJECT_POINTER, typename METHOD_POINTER>
        inline Functor( OBJECT_POINTER o, METHOD_POINTER m ) :  callable(),
        function_( new Kernel::command<R,TLIST,OBJECT_POINTER,METHOD_POINTER>( o, m ) ) {}

        //______________________________________________________________________
        //
        // clonable interface
        //______________________________________________________________________
        virtual callable  *clone() const { return new Functor(*this); } //!< \return cloned


        //______________________________________________________________________
        //
        // forwarding calls, using optimized parameter types
        // to avoid copy overhead
        //______________________________________________________________________

        //! forward no argument call \return call value
        inline R operator()(void) {
            assert(function_);
            return (*function_)();
        }

        //! forward one argument call
        /**
         \param p1 param1
         \return call value
         */
        inline R operator()(param1 p1)
        {
            assert(function_);
            return (*function_)(p1);
        }

        //! forward two arguments call
        /**
         \param p1 param1
         \param p2 param2
         \return call value
         */
        inline R operator()(param1 p1,
                            param2 p2)
        {
            assert( function_ );
            return (*function_)(p1,p2);
        }

        //! forward three arguments call
        /**
         \param p1 param1
         \param p2 param2
         \param p3 param3
         \return call value
         */
        inline R operator()(param1 p1,
                            param2 p2,
                            param3 p3)
        {
            assert( function_ );
            return (*function_)(p1,p2,p3);
        }

        //! forward four arguments call
        /**
         \param p1 param1
         \param p2 param2
         \param p3 param3
         \param p4 param4
         \return call value
         */
        inline R operator()(param1 p1,
                            param2 p2,
                            param3 p3,
                            param4 p4)
        {
            assert( function_ );
            return (*function_)(p1,p2,p3,p4);
        }

        //! forward five arguments call
        /**
         \param p1 param1
         \param p2 param2
         \param p3 param3
         \param p4 param4
         \param p5 param5
         \return call value
         */
        inline R operator()(param1 p1,
                            param2 p2,
                            param3 p3,
                            param4 p4,
                            param5 p5)
        {
            assert( function_ );
            return (*function_)(p1,p2,p3,p4,p5);
        }


        //! direct assignation for binder_first or manual setting
        /**
         \param proc a newly created callable
         */
        explicit Functor( callable * const proc ) noexcept : function_( proc ) { assert( proc ); }

    private:
        callable  *function_; //!< inner call

        //! destroy
        inline void destroy() noexcept
        {
            Object * const pObj = function_; // __DMC__ bug otherwise
            function_           = NULL;
            delete  pObj;
        }
    };


    namespace Kernel {

        //! first parameter binding
        /**
         inner typedefs perform all the types computations
         */
        template <typename incoming>
        class binder_first : public callable<typename incoming::result, typename incoming::arguments::tail>
        {
        public:
            typedef typename incoming::result                     R;        //!< return type alias
            typedef typename incoming::arguments::tail            TLIST;    //!< arguments alias
            typedef Functor<R,TLIST>                              outgoing; //!< return functor alias

            typedef typename incoming::arguments::head            bounded;       //!< bounded type
            typedef typename TypeTraits<bounded>::ParamType       bounded_param; //!< bounded parameter type

            Y_FUNCTOR_PARAMETERS(); //!< parameters alias

            //! cloneable interface by copy
            virtual callable<R,TLIST> *clone() const { return new binder_first( *this ); }

            //! constructor
            explicit binder_first( const incoming &f, bounded_param b ) :
            functor_( f ),
            bounded_( b )
            {}

            //! destructor
            virtual ~binder_first() noexcept {}



            //! 1->0 argument call
            inline R operator()(void)
            {
                return functor_(bounded_);
            }

            //! 2->1 argument call
            inline R operator()(param1 p1)
            {
                return functor_(bounded_,p1);
            }

            //! 3->2 arguments call
            inline R operator()(param1 p1, param2 p2)
            {
                return functor_(bounded_,p1,p2);
            }


        private:
            incoming functor_;   //!< functor copy semantics
            bounded  bounded_;   //!< first parameter value

            binder_first( const binder_first &other ) :
            functor_( other.functor_ ),
            bounded_( other.bounded_ )
            {
            }
        };
    }

    //! bind first parameter to make a new functor
    template <typename incoming>
    inline
    typename Kernel::binder_first<incoming>::outgoing
    bind_first( const incoming &f, typename Kernel::binder_first<incoming>::bounded_param p )
    {
        typedef typename Kernel::binder_first<incoming>::outgoing out_functor;
        typedef typename out_functor::callable                    out_callable;
        out_callable *proc = new Kernel::binder_first<incoming>( f, p );
        return  out_functor( proc );
    }

    //! make a functor from a C function
    template <typename R,typename T>
    inline Functor<R,TL1(T)> cfunctor( R (*cfn)(T) ) { return Functor<R,TL1(T)>( cfn ); }

    //! make a functor from a C function
    template <typename R,typename T,typename U>
    inline Functor<R,TL2(T,U)> cfunctor2( R (*cfn)(T,U) ) { return Functor<R,TL2(T,U)>( cfn ); }

    //! make a functor from a C function
    template <typename R,typename T,typename U,typename V>
    inline Functor<R,TL3(T,U,V)> cfunctor3( R (*cfn)(T,U,V) ) { return Functor<R,TL3(T,U,V)>( cfn ); }

}

#endif
