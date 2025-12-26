
//! \file

#ifndef Y_MKL_Tao2_Seq_Included
#define Y_MKL_Tao2_Seq_Included 1

#include "y/mkl/tao/1.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {
            namespace Hub
            {

                //! core multiplication of a row times a vector-like
                /**
                 \param xadd xadditiion
                 \param row  row-type
                 \param rhs  vector-type
                 \return row*rhs
                 */
                template <typename T,typename ROW, typename RHS> inline
                T MulCore(Cameo::Addition<T> & xadd,
                          const ROW          & row,
                          RHS &                rhs)
                {
                    xadd.ldz(); assert( row.size() == rhs.size() );
                    for(size_t j=rhs.size();j>0;--j)
                        xadd.addProd(row[j], rhs[j]);
                    return xadd.sum();
                }

                //! partial, SEQUENTIAL set
                /**
                 \param xadd perform additions
                 \param lhs  target vector
                 \param a    matrix
                 \param rhs  source vector
                 \param rlo  lower row index
                 \param rup  upper row index
                 */
                template <
                typename T,
                typename LHS,
                typename MAT,
                typename RHS
                > inline
                void MulSetSeq(Cameo::Addition<T> & xadd,
                               LHS                & lhs,
                               const MAT          & a,
                               RHS                & rhs,
                               const size_t         rlo,
                               const size_t         rup)
                {
                    for(size_t i=rup;i>=rlo;--i)
                        lhs[i] = MulCore(xadd,a[i],rhs);
                }

                //! partial, SEQUENTIAL  mul-add
                /**
                 \param xadd perform additions
                 \param lhs  target vector
                 \param a    matrix
                 \param rhs  source vector
                 \param rlo  lower row index
                 \param rup  upper row index
                 */
                template <
                typename T,
                typename LHS,
                typename MAT,
                typename RHS
                > inline
                void MulAddSeq(Cameo::Addition<T> & xadd,
                               LHS                & lhs,
                               const MAT          & a,
                               RHS                & rhs,
                               const size_t         rlo,
                               const size_t         rup)
                {
                    for(size_t i=rup;i>=rlo;--i)
                        lhs[i] += MulCore(xadd,a[i],rhs);
                }

                //! partial, SEQUENTIAL  mul-sub
                /**
                 \param xadd perform additions
                 \param lhs  target vector
                 \param a    matrix
                 \param rhs  source vector
                 \param rlo  lower row index
                 \param rup  upper row index
                 */
                template <
                typename T,
                typename LHS,
                typename MAT,
                typename RHS
                > inline
                void MulSubSeq(Cameo::Addition<T> & xadd,
                               LHS                & lhs,
                               const MAT          & a,
                               RHS                & rhs,
                               const size_t         rlo,
                               const size_t         rup)
                {
                    for(size_t i=rup;i>=rlo;--i)
                        lhs[i] -= MulCore(xadd,a[i],rhs);
                }


            }


            //! SEQUENTIAL matrix/vector mul-set
            /**
             \param xadd perform additions
             \param lhs  target vector
             \param a    matrix
             \param rhs  source vector
             */
            template <
            typename T,
            typename LHS,
            typename MAT,
            typename RHS
            > inline
            void Mul(Cameo::Addition<T> &xadd, LHS &lhs, const MAT &a, RHS &rhs)
            {
                assert(a.rows==lhs.size());
                assert(a.cols==rhs.size());
                Hub::MulSetSeq(xadd, lhs, a, rhs, 1, a.rows);
            }

            //! SEQUENTIAL matrix/vector mul-add
            /**
             \param xadd perform additions
             \param lhs  target vector
             \param a    matrix
             \param rhs  source vector
             */
            template <
            typename T,
            typename LHS,
            typename MAT,
            typename RHS
            > inline
            void MulAdd(Cameo::Addition<T> &xadd, LHS &lhs, const MAT &a, RHS &rhs)
            {
                assert(a.rows==lhs.size());
                assert(a.cols==rhs.size());
                Hub::MulAddSeq(xadd, lhs, a, rhs, 1, a.rows);
            }

            //! SEQUENTIAL matrix/vector mul-sub
            /**
             \param xadd perform additions
             \param lhs  target vector
             \param a    matrix
             \param rhs  source vector
             */
            template <
            typename T,
            typename LHS,
            typename MAT,
            typename RHS
            > inline
            void MulSub(Cameo::Addition<T> &xadd, LHS &lhs, const MAT &a, RHS &rhs)
            {
                assert(a.rows==lhs.size());
                assert(a.cols==rhs.size());
                Hub::MulSubSeq(xadd, lhs, a, rhs, 1, a.rows);
            }

        }

    }

}

#endif // !Y_MKL_Tao2_Seq_Included

