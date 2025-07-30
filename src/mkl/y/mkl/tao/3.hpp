
//! \file

#ifndef Y_MKL_Tao3_Included
#define Y_MKL_Tao3_Included 1

#include "y/mkl/tao/2.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

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
                {
                    for(size_t j=nc;j>0;--j)
                    {
                        xadd.ldz();
                        for(size_t k=lhs.cols;k>0;--k)
                            xadd.addProd(lhs[i][k],rhs[k][j]);
                        
                        mat[i][j] = xadd.sum();
                    }
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
                        G[i][j] = G[j][i] = Dot(xadd,M_i,M[j]);
                }
            }

        }

    }

}

#endif

