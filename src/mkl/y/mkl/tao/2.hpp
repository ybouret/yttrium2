
//! \file

#ifndef Y_MKL_Tao2_Included
#define Y_MKL_Tao2_Included 1

#include "y/mkl/tao/1.hpp"
#include "y/mkl/tao/broker/linear.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {



            namespace Hub
            {

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

                //! partial, sequential set
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

                //! partial, sequential  operations
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


            }


            //! sequential matrix/vector mul-set
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

            //! sequential matrix/vector operations
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


            namespace Hub
            {
                //! parallel matrix/vector mul-set
                /**
                 \param tile   operating tile
                 \param lhs    target vector
                 \param a      matrix
                 \param rhs    source vector
                 */
                template <
                typename T,
                typename LHS,
                typename MAT,
                typename RHS
                >
                inline void MulSetPar(Lockable  &,
                                      Tile1D    &tile,
                                      LHS       &lhs,
                                      const MAT &a,
                                      RHS       &rhs)
                {
                    assert(0!=tile.entry);
                    assert(tile.offset>0);
                    { Y_Giant_Lock(); std::cerr << "Mul in " << tile << std::endl; }
                    Hub::MulSetSeq( *tile.as< Cameo::Addition<T> * >(), lhs, a, rhs, tile.offset, tile.utmost );
                }

                //! parallel matrix/vector mul-set
                /**
                 \param tile   operating tile
                 \param lhs    target vector
                 \param a      matrix
                 \param rhs    source vector
                 */
                template <
                typename T,
                typename LHS,
                typename MAT,
                typename RHS
                >
                inline void MulAddPar(Lockable  &,
                                      Tile1D    &tile,
                                      LHS       &lhs,
                                      const MAT &a,
                                      RHS       &rhs)
                {
                    assert(0!=tile.entry);
                    assert(tile.offset>0);
                    Hub::MulAddSeq( *tile.as< Cameo::Addition<T> * >(), lhs, a, rhs, tile.offset, tile.utmost );
                }


            }

            //! parallel matrix vector mul-set
            /**
             \param broker perform additions
             \param lhs    target vector
             \param a      matrix
             \param rhs    source vector
             */
            template <
            typename T,
            typename LHS,
            typename MAT,
            typename RHS
            > inline
            void Mul(LinearBroker<T> &broker, LHS &lhs, const MAT &a, RHS &rhs)
            {
                broker->remap(a.rows);
                broker->run(Hub::MulSetPar<T,LHS,MAT,RHS>,lhs,a,rhs);
            }

            //! parallel matrix vector mul-addr
            /**
             \param broker perform additions
             \param lhs    target vector
             \param a      matrix
             \param rhs    source vector
             */
            template <
            typename T,
            typename LHS,
            typename MAT,
            typename RHS
            > inline
            void MulAdd(LinearBroker<T> &broker, LHS &lhs, const MAT &a, RHS &rhs)
            {
                broker->remap(a.rows);
                broker->run(Hub::MulAddPar<T,LHS,MAT,RHS>,lhs,a,rhs);
            }




        }

    }

}

#endif // !Y_MKL_Tao2_Included

