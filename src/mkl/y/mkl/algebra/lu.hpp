
//! \file

#ifndef Y_MKL_LU_Included
#define Y_MKL_LU_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/container/matrix.hpp"
#include "y/container/gradual.hpp"

namespace Yttrium
{
    namespace MKL
    {
        //______________________________________________________________________
        //
        //
        //
        //! LU decomposition
        //
        //
        //______________________________________________________________________
        template <typename T>
        class LU : public Container, public Releasable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type);
            typedef typename ScalarFor<T>::Type ScalarType;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit LU(const size_t maxDim=0);
            virtual ~LU() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   release()    noexcept;
            virtual size_t size() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! ensure/adjust size
            LU & make(const size_t n);

            //! decompose matrix
            /**
             \param a a square matrix
             \return true if not singular and decomposed
             */
            bool build(Matrix<T> &a);

            //! \return determinant of a decomposed matrix
            T    det(const Matrix<T> &);

            //! b = inv(a) * b
            void solve(const Matrix<T> &a, Writable<T> &b);

            void inv(const Matrix<T> &a, Matrix<T> &ia);


        private:
            class Code;
            Y_Disable_Copy_And_Assign(LU); //!< discarding
            void release_() noexcept;      //!< release code
            Code *code;                    //!< inner code
        };
    }

}


#endif

