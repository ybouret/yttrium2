

//! \file



#ifndef Y_MKL_ZRid_Included
#define Y_MKL_ZRid_Included 1

#include "y/mkl/root/zfind.hpp"


namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! Modified Ridder's method
        //
        //
        //______________________________________________________________________
        template <typename T>
        class ZRid : public ZFind<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename ZFind<T>::FunctionType FunctionType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ZRid() noexcept; //!< setup
            virtual ~ZRid() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;
            virtual T            lookup(Triplet<T> &x, Triplet<T> &f, FunctionType &F);

        private:
            Y_Disable_Copy_And_Assign(ZRid); //!< discarding
        };

    }

}



#endif

