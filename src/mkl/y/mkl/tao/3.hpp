
//! \file

#ifndef Y_MKL_Tao3_Included
#define Y_MKL_Tao3_Included 1

#include "y/mkl/tao/2.hpp"
#include "y/mkl/tao/seq/3.hpp"
#include "y/mkl/tao/broker/matrix.hpp"
#include "y/mkl/tao/broker/upper-diagonal.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            namespace Hub
            {
                //! parallel matrix/vector mul-sub
                /**
                 \param tile   operating tile
                 \param lhs    target vector
                 \param a      matrix
                 \param rhs    source vector
                 */
                template <
                typename T,
                typename MAT,
                typename LHS,
                typename RHS
                >
                inline void  MMulPar(Lockable  &,
                                     Tile2D    &tile,
                                     MAT       &a,
                                     LHS       &lhs,
                                     RHS       &rhs)
                {
                    assert(0!=tile.entry);
                    Cameo::Addition<T> & xadd = *tile.as< Cameo::Addition<T> * >();
                    for(size_t h=tile.h;h>0;--h)
                    {
                        const MatrixSegment &seg = tile[h];
                        const size_t           i = seg.start.y;
                        typename MAT::Row   &a_i = a[i];
                        for(size_t j=seg.start.x,n=seg.width;n>0;--n,++j)
                            a_i[j] = MMulCore(xadd,i,j,lhs,rhs);
                    }
                }
            }

            //! matrix/matrix multiplication
            /**
             \param broker dispatch additions
             \param mat    target matrix
             \param lhs    lhs matrix
             \param rhs    rhs matrix
             */
            template <typename T,
            typename MAT,
            typename LHS,
            typename RHS
            > inline
            void MMul( MatrixBroker<T> &broker, MAT &mat, LHS &lhs, RHS &rhs)
            {
                assert(lhs.rows == mat.rows);
                assert(lhs.cols == rhs.rows);
                assert(rhs.cols == mat.cols);
                broker.prep(mat);
                broker->run( Hub::MMulPar<T,MAT,LHS,RHS>, mat, lhs, rhs );
            }



            namespace Hub
            {
                //! parallel Gram computation over a tile
                /**
                 \param tile   operating tile
                 \param G      target matrix
                 \param M      source matrix
                 */
                template <
                typename T,
                typename TARGET,
                typename SOURCE>
                inline void  GramPar(Lockable          &,
                                     UpperDiagonalTile & tile,
                                     TARGET            & G,
                                     const SOURCE      & M)
                {
                    assert(0!=tile.entry);
                    Cameo::Addition<T> & xadd = *tile.as< Cameo::Addition<T> * >();
                    for(size_t h=tile.h;h>0;--h)
                    {
                        const UpperDiagonalSegment &seg = tile[h];
                        const size_t           i = seg.start.y;
                        for(size_t j=seg.start.x,n=seg.width;n>0;--n,++j)
                            G[i][j] = G[j][i] = GramCore(xadd,i,j,M);
                    }
                }
            }

            //! Gram's matrix
            /**
             \param broker par/seq broker
             \param G    destination matrix = M*M'
             \param M    source matrix
             */
            template <typename T,
            typename TARGET,
            typename SOURCE> inline
            void Gram(UpperDiagonalBroker<T> &broker,TARGET &G, SOURCE &M)
            {
                assert(G.rows == M.rows);
                assert(G.rows == G.cols);
                broker.prep(G);
                broker->run( Hub::GramPar<T,TARGET,SOURCE>, G, M);
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

#endif // !Y_MKL_Tao3_Included

