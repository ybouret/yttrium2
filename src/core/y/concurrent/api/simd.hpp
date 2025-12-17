
//! \file

#ifndef Y_Concurrent_SIMD_Included
#define Y_Concurrent_SIMD_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Single Instruction Multiple Data
        //
        //
        //______________________________________________________________________
        class SIMD : public CountedObject, public Parallel
        {
        public:
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            explicit SIMD() noexcept;

        public:
            //cleanup
            virtual ~SIMD() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            virtual void operator()( Kernel & ) noexcept = 0; //!< execute kernel for each context

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! run host.meth(context) \param host persistent host \param meth method pointer
            template <typename HOST, typename METH> inline
            void operator()(HOST &host, METH meth)
            {
                Kernel kernel(&host,meth);
                (*this)(kernel);
            }

            //! run host.meth(contex,arg1)
            /**
             \param host persistent host
             \param meth method pointer
             \param arg1 persistent argument
             */
            template <typename HOST, typename METH, typename ARG1> inline
            void operator()(HOST &host, METH meth, ARG1 &arg1)
            {
                Wrapper1<HOST,METH,ARG1> wrapper = { host, meth, arg1 };
                (*this)(wrapper, & Wrapper1<HOST,METH,ARG1>::call );
            }


        private:
            Y_Disable_Copy_And_Assign(SIMD); //!< discarding

            //! wrapper for extra argument method
            template <typename HOST, typename METH, typename ARG1>
            struct Wrapper1
            {
                HOST & host; //!< host
                METH   meth; //!< method pointer
                ARG1 & arg1; //!< argument

                //! \param ctx thread context
                inline void call(const Context &ctx) {
                    (host.*meth)(ctx,arg1);
                }

            };

        };

    }

}

#endif // !Y_Concurrent_SIMD_Included

