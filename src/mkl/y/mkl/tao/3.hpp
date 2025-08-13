
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

            //! left multiplication of a diagonal matrix as a vector
            /**
             \param target matrix[r][c]
             \param diag   vector[r]
             \param source matrix[r][c]
             */
            template <
            typename TARGET,
            typename DIAG,
            typename SOURCE> inline
            void DMul( TARGET &target, DIAG &diag, SOURCE &source )
            {
                assert(target.rows==source.rows);
                assert(target.cols==source.cols);
                assert(diag.size()==target.rows);
                const size_t nc = target.cols;
                for(size_t i=target.rows;i>0;--i)
                {
                    const typename SOURCE::Row &src = source[i];
                    typename       TARGET::Row &tgt = target[i];
                    typename DIAG::ConstType   &fac = diag[i];
                    for(size_t j=nc;j>0;--j) tgt[j] = fac * src[j];
                }
            }

            namespace Hub
            {
                
                //! op(target,source) \param target target matrix \param source source matrix \param op operation
                template <typename TARGET,typename SOURCE, typename OP> inline
                void MatrixApply(TARGET &target, SOURCE &source, OP &op)
                {
                    assert(target.rows==source.rows);
                    assert(target.cols==source.cols);

                    typename TARGET::Type *      tgt = target();
                    typename SOURCE::ConstType * src = source();
                    for(size_t i=target.items;i>0;--i)
                    {
                        op( *(tgt++), *(src++) );
                    }
                }
            }

            //! target += source \param target target matrix \param source source matrix
            template <typename TARGET,typename SOURCE> inline
            void MAdd(TARGET &target, SOURCE &source)
            {
                Hub::MatrixApply(target,source, Hub::AddOp1<typename TARGET::Type,typename SOURCE::Type> );
            }

            //! target -= source \param target target matrix \param source source matrix
            template <typename TARGET,typename SOURCE> inline
            void MSub(TARGET &target, SOURCE &source)
            {
                Hub::MatrixApply(target,source, Hub::SubOp1<typename TARGET::Type,typename SOURCE::Type> );
            }

        }

    }

}

#endif

