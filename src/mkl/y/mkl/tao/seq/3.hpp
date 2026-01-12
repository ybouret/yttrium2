
//! \file

#ifndef Y_MKL_Tao3_Seq_Included
#define Y_MKL_Tao3_Seq_Included 1

#include "y/container/matrix.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            namespace Hub
            {

                //! compute product element
                /**
                 \param xadd for additions
                 \param i    row index
                 \param j    col index
                 \param lhs  lhs matrix
                 \param rhs  rhs matrix
                 \return sum_k(lhs[i][k],rhs[k][j])
                 */
                template <typename T, typename LHS, typename RHS> inline
                T MMulCore(Cameo::Addition<T> &xadd,
                           const size_t         i,
                           const size_t         j,
                           LHS                & lhs,
                           RHS                & rhs)
                {
                    assert(lhs.cols == rhs.rows);
                    xadd.ldz();
                    for(size_t k=lhs.cols;k>0;--k)
                        xadd.addProd(lhs[i][k],rhs[k][j]);
                    return xadd.sum();
                }

            }


            //! matrix/matrix multiplication
            /**
             \param xadd perform additions
             \param mat  target matrix
             \param lhs  lhs matrix
             \param rhs  rhs matrix
             */
            template <typename T,
            typename MAT,
            typename LHS,
            typename RHS
            > inline
            void MMul( Cameo::Addition<T> &xadd, MAT &mat, LHS &lhs, RHS &rhs)
            {
                const size_t nr = mat.rows;
                const size_t nc = mat.cols;
                assert(lhs.rows == mat.rows);
                assert(lhs.cols == rhs.rows);
                assert(rhs.cols == mat.cols);

                for(size_t i=nr;i>0;--i)
                    for(size_t j=nc;j>0;--j)
                        mat[i][j] = Hub::MMulCore(xadd,i,j,lhs,rhs);

            }


            namespace Hub
            {
                template <typename T, typename MATRIX> inline
                T GramCore(Cameo::Addition<T> &xadd,
                           const size_t         i,
                           const size_t         j,
                           const MATRIX &       M)
                {
                    return Dot(xadd,M[i],M[j]);
                }
            }


            //! Gram's matrix
            /**
             \param xadd perform additions
             \param G    destination matrix = M*M'
             \param M    source matrix
             */
            template <typename T,
            typename TARGET,
            typename SOURCE> inline
            void Gram( Cameo::Addition<T> &xadd, TARGET &G, SOURCE &M)
            {
                assert(G.rows==M.rows);
                assert(G.cols==M.rows);
                for(size_t i=M.rows;i>0;--i)
                {
                    const typename SOURCE::Row &M_i = M[i];
                    G[i][i] = Dot(xadd,M_i,M_i);
                    for(size_t j=i-1;j>0;--j)
                        G[i][j] = G[j][i] = Hub::GramCore(xadd,i,j,M);
                }
            }


        }

    }

}

#endif // !Y_MKL_Tao3_Seq_Included
