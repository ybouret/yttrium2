
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
            Y_Args_Declare(T,Type); //!< aliases
            typedef typename ScalarFor<T>::Type ScalarType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit LU(const size_t=0); //!< setup with optional max dimension
            virtual ~LU() noexcept;      //!< cleanup

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

            //! ensure/adjust \param n size \return *this
            LU & make(const size_t n);

            //! decompose matrix
            /**
             \param a a square matrix
             \return true if not singular and decomposed
             */
            bool build(Matrix<T> &a);

            //! \return determinant of a decomposed matrix
            T    det(const Matrix<T> &);

            //! solve \param a decomposed matrix \param b b = inv(a) * b
            void solve(const Matrix<T> &a, Writable<T> &b);

            //! inverse \param a decomposed matrix \param ia a^(-1)
            void inv(const Matrix<T> &a, Matrix<T> &ia);


            template <typename U> inline
            T determinant(const Matrix<U> &M)
            {
                Matrix<T> a(CopyOf,M);
                return build(a) ? det(a) : T(0);
            }


        private:
            class Code;
            Y_Disable_Copy_And_Assign(LU); //!< discarding
            void release_() noexcept;      //!< release code
            Code *code;                    //!< inner code
        };
    }

}


#endif

