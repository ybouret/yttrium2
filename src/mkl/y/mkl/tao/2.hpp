
//! \file

#ifndef Y_MKL_Tao2_Included
#define Y_MKL_Tao2_Included 1

#include "y/mkl/tao/1.hpp"
#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"
#include "y/cameo/caddy.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            typedef Concurrent::Divide::Tile1D<size_t>     Tile1D;
            typedef Concurrent::Divide::CxxTiles1D<size_t> Tiles1D;
            typedef Concurrent::Spawn<Tiles1D>             LinearSpawn;
            typedef LinearSpawn::Pointer                   LinearEngine;

            class LinearBroker
            {
            public:
                explicit LinearBroker(const LinearEngine &);
                virtual ~LinearBroker() noexcept;

            protected:
                LinearEngine engine;

            private:
                Y_Disable_Copy_And_Assign(LinearBroker);
            };

            




            //! matrix vector multiplication
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
                const size_t nr = a.rows; assert(lhs.size()==nr);
                const size_t nc = a.cols; assert(rhs.size()==nc);
                for(size_t i=nr;i>0;--i)
                {
                    const typename MAT::Row &a_i = a[i];
                    xadd.ldz();
                    for(size_t j=nc;j>0;--j)
                        xadd.addProd(a_i[j], rhs[j]);
                    lhs[i] = xadd.sum();
                }
            }

        }

    }

}

#endif // !Y_MKL_Tao2_Included

