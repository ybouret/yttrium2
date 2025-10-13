//! \file
#ifndef YACK_FUNCTOR_CALL_INCLUDED
#define YACK_FUNCTOR_CALL_INCLUDED 1


#include "y/object.hpp"
#include "y/type/traits.hpp"

namespace Yttrium
{

    namespace Kernel
    {

        //______________________________________________________________________
        //
        //
        //! callable interface construction
        //
        //______________________________________________________________________

#define YACK_CALLABLE_PROTOTYPE()                 \
/**/  private:                                    \
/**/   Y_Disable_Copy_And_Assign(callable);    \
/**/  public:                                     \
/**/    explicit callable() noexcept : Object() {} \
/**/    virtual ~callable() noexcept {}            \
/**/    virtual callable *clone() const = 0


        //! Helper to declare parameters
#define Y_FUNCTOR_PARAM(TYPE) typename TypeTraits<TYPE>::ParamType

        //! memory management
#define YACK_CALLABLE_OBJECT() : public  Object

        //! defines the behavior of a generic callable object
        /**
         the parameters are send thru a typelist
         \return callable
         */
        template <typename R,class TLIST>
        class callable YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
        };

        //! \return no argument callable type
        template <typename R>
        class callable<R,NullType> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator() (void) = 0; //!< interface for no argument call
        };

        //! \return one argument callable type
        template <typename R, typename P1>
        class callable<R,TL1(P1)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()( Y_FUNCTOR_PARAM(P1) ) = 0;
        };

        //! \return two arguments callable type
        template <typename R, typename P1, typename P2>
        class callable<R,TL2(P1,P2)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()(Y_FUNCTOR_PARAM(P1),
                                 Y_FUNCTOR_PARAM(P2))= 0;
        };

        //! \return three arguments callable type
        template <typename R, typename P1, typename P2, typename P3>
        class callable<R,TL3(P1,P2,P3)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()(Y_FUNCTOR_PARAM(P1),
                                 Y_FUNCTOR_PARAM(P2),
                                 Y_FUNCTOR_PARAM(P3) )= 0;
        };

        //! \return four arguments callable type
        template <typename R, typename P1, typename P2, typename P3, typename P4>
        class callable<R,TL4(P1,P2,P3,P4)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()(Y_FUNCTOR_PARAM(P1),
                                 Y_FUNCTOR_PARAM(P2),
                                 Y_FUNCTOR_PARAM(P3),
                                 Y_FUNCTOR_PARAM(P4)
                                 ) = 0;
        };

        //! \return five arguments callable type
        template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
        class callable<R,TL5(P1,P2,P3,P4,P5)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()(Y_FUNCTOR_PARAM(P1),
                                 Y_FUNCTOR_PARAM(P2),
                                 Y_FUNCTOR_PARAM(P3),
                                 Y_FUNCTOR_PARAM(P4),
                                 Y_FUNCTOR_PARAM(P5)
                                 ) = 0;
        };

        //! \return siz arguments callable type
        template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
        class callable<R,TL6(P1,P2,P3,P4,P5,P6)> YACK_CALLABLE_OBJECT()
        {
            YACK_CALLABLE_PROTOTYPE();
            virtual R operator()(Y_FUNCTOR_PARAM(P1),
                                 Y_FUNCTOR_PARAM(P2),
                                 Y_FUNCTOR_PARAM(P3),
                                 Y_FUNCTOR_PARAM(P4),
                                 Y_FUNCTOR_PARAM(P5),
                                 Y_FUNCTOR_PARAM(P6)
                                 ) = 0;
        };




        //! compute parameters aliases
#define Y_FUNCTOR_PARAMETERS() \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,0,EmptyType>::Result>::ParamType param1; \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,1,EmptyType>::Result>::ParamType param2; \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,2,EmptyType>::Result>::ParamType param3; \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,3,EmptyType>::Result>::ParamType param4; \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,4,EmptyType>::Result>::ParamType param5; \
typedef typename TypeTraits< typename TL::SafeTypeAt<TLIST,5,EmptyType>::Result>::ParamType param6


    }

}

#endif // !YACK_FUNCTOR_CALL_INCLUDED
