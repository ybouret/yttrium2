//! \file

#ifndef Y_MKL_Algebra_TriDiag_Included
#define Y_MKL_Algebra_TriDiag_Included 1

#include "y/container/matrix.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! Tri-Diagonal Matrix (a,b,c)
        //
        //
        //__________________________________________________________________
        template <typename T>
        class TriDiag
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit TriDiag(const size_t n); //!< setup \param n dimensions
            virtual ~TriDiag() noexcept;      //!< cleanup


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return crc32 of used data
            uint32_t crc32() const noexcept;
            
            //! try to solve
            /**
             \param u response
             \param r rhs
             \return true if r == *this * u
             */
            bool  solve(Writable<T> &u, const Readable<T> &r);

            //! try to solve with a foreign diagonal
            /**
             \param u response
             \param r rhs
             \param B foreign diagonal
             \return true if u was computed
             */
            bool  solve(Writable<T> &u, const Readable<T> &r, const Readable<T> &B);


            //! res = *this * rhs
            /**
             \param xadd for inner additions
             \param res  result
             \param rhs  rhs
             */
            template <typename RES, typename RHS> inline
            void mul(Cameo::Addition<T> &xadd, RES &res, RHS &rhs) const
            {

                const size_t n = size;
                switch(n)
                {
                    case 0: return;
                    case 1: res[1] = b[1]*rhs[1]; return;
                    default:
                        break;
                }

                res[1] = b[1]*rhs[1] + c[1]*rhs[2];
                const size_t nm=n-1;
                for(size_t i=nm,im=i-1,ip=i+1;i>1;--i,--im,--ip)
                {
                    const T A = a[i] * rhs[im];
                    const T B = b[i] * rhs[i];
                    const T C = c[i] * rhs[ip];
                    res[i] = xadd(A,B,C);
                }
                res[n] = a[n] * rhs[nm] + b[n] * rhs[n];
            }

            //! display as a dense matrix
            inline friend std::ostream & operator<<(std::ostream &os, const TriDiag &self)
            {
                Matrix<T> M(self.size,self.size);
                self.sendTo(M);
                os << M;
                return os;
            }

        private:
            Y_Disable_Copy_And_Assign(TriDiag); //!< discarding
            class Code;
            Code *code; //!< inner code
            
        public:
            Writable<T>  & a;     //!< a[2..size]
            Writable<T>  & b;     //!< b[1..size]
            Writable<T>  & c;     //!< c[1..size-1]
            const size_t & size;  //!< dimensions
            const T      & zero;  //!< constant zero value

            //! full access mimicking
            /**
             \param i 1<=i<=size
             \param j 1<=j<=size
             \return copy of target value
             */
            T operator()(const size_t i, const size_t j) const;

            //! fill dense matrix \param M target matrix
            template <typename U>
            inline void sendTo(Matrix<U> &M) const
            {
                assert(M.rows==size);
                assert(M.cols==M.rows);
                const TriDiag &self = *this;
                const size_t   n    = self.size;
                for(size_t i=n;i>0;--i)
                {
                    Writable<U> &M_i = M[i];
                    for(size_t j=n;j>0;--j) M_i[j] = self(i,j);
                }
            }

        };
    }
}

#endif

