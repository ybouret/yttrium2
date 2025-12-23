
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

            typedef Concurrent::Divide::Tile1D<size_t>     Tile1D;       //!< alias
            typedef Concurrent::Divide::CxxTiles1D<size_t> Tiles1D;      //!< alias
            typedef Concurrent::Spawn<Tiles1D>             LinearSpawn;  //!< alias
            typedef LinearSpawn::Pointer                   LinearEngine; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! will split operations on matrix rows/cols
            //
            //
            //__________________________________________________________________
            template <typename T>
            class LinearBroker : public Ingress< LinearSpawn >
            {
            public:
                //______________________________________________________________
                //
                //
                // definitions
                //
                //______________________________________________________________
                typedef Cameo::Addition<T> XAddition; //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup from shared linear spawn \param eng shared engine
                inline explicit LinearBroker(const LinearEngine &eng) :
                engine(eng),
                caddy()
                {
                    engine->link( caddy.adjust(engine->size()).head );
                }

                //! cleanup
                inline virtual ~LinearBroker() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                /*
                 inline void relink() noexcept
                 {
                 engine->link( caddy.head );
                 }
                 */

                //! \return first XAddition
                inline XAddition & xadd() noexcept
                {
                    assert( caddy.head );
                    return *caddy.head;
                }


            private:
                Y_Disable_Copy_And_Assign(LinearBroker); //!< disable

                inline virtual ConstInterface & locus() const noexcept { return *engine; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                LinearEngine     engine; //!< shared engine
                Cameo::Caddy<T>  caddy;  //!< xadditions
            };


            namespace Hub
            {
                //! partial operations
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
                void MulProc(Cameo::Addition<T> & xadd,
                             LHS                & lhs,
                             const MAT          & a,
                             RHS                & rhs,
                             const size_t         rlo,
                             const size_t         rup)
                {
                    const size_t nc = a.cols; assert(rhs.size()==nc);
                    for(size_t i=rup;i>=rlo;--i)
                    {
                        const typename MAT::Row &a_i = a[i];
                        xadd.ldz();
                        for(size_t j=nc;j>0;--j)
                            xadd.addProd(a_i[j], rhs[j]);
                        lhs[i] = xadd.sum();
                    }
                }
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
            void Mul(Cameo::Addition<T> &xadd, LHS &lhs, const MAT &a, RHS &rhs)
            {
                assert(a.rows==lhs.size());
                assert(a.cols==rhs.size());
                Hub::MulProc(xadd, lhs, a, rhs, 1, a.rows);
            }

            namespace Hub
            {
                //! parallel matrix/vector operations
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
                inline void Mul(Lockable  &,
                                Tile1D    &tile,
                                LHS       &lhs,
                                const MAT &a,
                                RHS       &rhs)
                {
                    assert(0!=tile.entry);
                    assert(tile.offset>0);
                    { Y_Giant_Lock(); std::cerr << "Mul in " << tile << std::endl; }
                    Cameo::Addition<T> & xadd = *tile.as< Cameo::Addition<T> * >();
                    Hub::MulProc(xadd, lhs, a, rhs, tile.offset, tile.utmost );
                }
            }

            //! parallel matrix vector operations
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
                broker->run(Hub::Mul<T,LHS,MAT,RHS>,lhs,a,rhs);
            }




        }

    }

}

#endif // !Y_MKL_Tao2_Included

