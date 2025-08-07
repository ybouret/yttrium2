//! \file

#ifndef Y_MKL_Derivatives_Interface_Included
#define Y_MKL_Derivatives_Interface_Included 1

#include "y/object.hpp"
#include "y/counted.hpp"
#include "y/mkl/function-wrapper-1d.hpp"
#include "y/mkl/function-wrapper-nd.hpp"
#include "y/mkl/interval.hpp"
#include "y/container/writable.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            //__________________________________________________________________
            //
            //
            //
            //! Common code for Derivatives
            //
            //
            //__________________________________________________________________
            class Derivatives : public Object, public Counted
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const CallSign; //!< Derivatives
                

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                static void UnderflowException();         //!< step size too small
                static void SingularFunctionException();  //!< unexpected function behavior
                static void OutOfDomainException();       //!< data point is out of definition domain

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                virtual ~Derivatives() noexcept; //!< cleanup
            protected:
                explicit Derivatives() noexcept; //!< setup

            private:
                Y_Disable_Copy_And_Assign(Derivatives);
            };
        }


        //______________________________________________________________________
        //
        //
        //
        //! Numerical Derivatives with Interval control
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Derivatives : public Kernel::Derivatives
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Function<T,T>                       FunctionType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Derivatives();            //!< setup
            virtual ~Derivatives() noexcept;   //!< cleanup


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //__________________________________________________________________
            //
            //! internal computation by modified Ridder's Method
            //__________________________________________________________________
            T compute1D(FunctionType &F, const T x0, const T h, const Interval<T> &I);


            //__________________________________________________________________
            //
            //! code wrapper for 1D function
            //__________________________________________________________________
            template <typename FUNCTION> inline
            T operator()(FUNCTION &F, const T x0, const T h, const Interval<T> &I)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                return compute1D(FW,x0,h,I);
            }

            //__________________________________________________________________
            //
            //! code wrapper for gradient
            //__________________________________________________________________
            template <typename SCALAR_FIELD> inline
            void operator()(Writable<T>                   &dFdX,
                            SCALAR_FIELD                  &F,
                            const Readable<T>             &X,
                            const Readable<T>             &H,
                            const Readable< Interval<T> > &I)
            {
                assert(dFdX.size() == X.size() );
                assert(dFdX.size() == H.size() );
                assert(dFdX.size() == I.size() );
                const size_t n = dFdX.size();
                for(size_t i=n;i>0;--i)
                {
                    WrapperND<T,T,SCALAR_FIELD> FW(F,X,i);
                    dFdX[i] = compute1D(FW,X[i],H[i],I[i]);
                }
            }

            
        private:
            Y_Disable_Copy_And_Assign(Derivatives);
            class Code;
            Code *code;
        };

    }
}

#endif

