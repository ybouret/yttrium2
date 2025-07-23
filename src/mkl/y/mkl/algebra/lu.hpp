
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


            //! compute determinant
            /**
             \param M compatible matrix, copied
             \return det(M)
             */
            template <typename U> inline
            T determinant(const Matrix<U> &M)
            {
                assert(M.isSquare());
                Matrix<T> a(CopyOf,M);
                return (a.rows>0 && build(a)) ? det(a) : T(0);
            }

            template <typename U> inline
            bool inverse(Matrix<T> &iM, const Matrix<U> &M)
            {
                Matrix<T> a(CopyOf,M);
                if( !build(a) ) { iM.ld(0); return false; }
                inv(a,iM);
                return true;
            }

            template <typename U, typename V> inline
            void adjoint(Matrix<U> &A, const Matrix<V> &M)
            {
                assert(M.isSquare());
                assert(A.gotSameMetricsThan(M));
                const size_t n = M.rows;
                switch(n)
                {
                    case 0: return;
                    case 1: A[1][1] = U(1); return;
                    default:
                        break;
                }

                const U      _0(0);
                const size_t m=n-1; assert(m>0);
                Matrix<T> a(m,m);
                for(size_t i=n;i>0;--i)
                {
                    for(size_t j=n;j>0;--j)
                    {
                        a.assign(MinorOf,i,j,M);
                        if(build(a))
                        {
                            A[j][i] = (0 == ((i+j) & 1) ) ? det(a) : -det(a);
                        }
                        else
                        {
                            A[j][i] = _0;
                        }
                    }
                }

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

