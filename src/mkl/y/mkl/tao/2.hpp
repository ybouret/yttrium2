
//! \file

#ifndef Y_MKL_Tao2_Included
#define Y_MKL_Tao2_Included 1

#include "y/mkl/tao/1.hpp"
#include "y/mkl/tao/seq/2.hpp"
#include "y/mkl/tao/broker/linear.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            
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

                //! parallel matrix/vector mul-add
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

                //! parallel matrix/vector mul-sub
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
                inline void MulSubPar(Lockable  &,
                                      Tile1D    &tile,
                                      LHS       &lhs,
                                      const MAT &a,
                                      RHS       &rhs)
                {
                    assert(0!=tile.entry);
                    assert(tile.offset>0);
                    Hub::MulSubSeq( *tile.as< Cameo::Addition<T> * >(), lhs, a, rhs, tile.offset, tile.utmost );
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

            //! parallel matrix vector mul-add
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

            //! parallel matrix vector mul-sub
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
            void MulSub(LinearBroker<T> &broker, LHS &lhs, const MAT &a, RHS &rhs)
            {
                broker->remap(a.rows);
                broker->run(Hub::MulSubPar<T,LHS,MAT,RHS>,lhs,a,rhs);
            }




        }

    }

}

#endif // !Y_MKL_Tao2_Included

