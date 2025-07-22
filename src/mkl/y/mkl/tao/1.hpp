
//! \file

#ifndef Y_MKL_Tao1_Included
#define Y_MKL_Tao1_Included 1

#include "y/cameo/addition.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            //! target[1..target.size()] = source[1..target.size()]
            /**
             \param target target sequence
             \param source source sequence, larger than target
             */
            template <typename TARGET, typename SOURCE> inline
            void Load(TARGET &target, SOURCE &source)
            {
                assert(source.size()>=target.size());
                for(size_t i=target.size();i>0;--i)
                {
                    target[i] = source[i];
                }
            }

            //! \return lhs*rhs
            /**
             \param xadd perform additions
             \param lhs  lhs sequence
             \param rhs  rhs sequence
             */
            template <typename T, typename LHS, typename RHS> inline
            T Dot(Cameo::Addition<T> &xadd, LHS &lhs, RHS &rhs)
            {
                assert( lhs.size() == rhs.size() );
                xadd.ldz();
                for(size_t i=lhs.size();i>0;--i)
                    xadd.addProd(lhs[i],rhs[i]);
                return xadd.sum();
            }


            namespace Hub
            {
                template <typename T,const bool SCALAR>
                struct Norm2;

                template <typename T>
                struct Norm2<T,true>
                {
                    Y_Args_Expose(T,Type);
                    typedef T OutputType;

                    static inline void Push(Cameo::Addition<OutputType> & xadd,
                                            ConstType &                   scal)
                    {
                        const T res = scal*scal;
                        xadd << res;
                    }
                };

                template <typename T>
                struct Norm2<T,false>
                {
                    Y_Args_Expose(T,Type);
                    typedef typename T::Type OutputType;

                    static inline void Push(Cameo::Addition<OutputType> & xadd,
                                            ConstType &                   vect)
                    {
                        for(size_t i=T::DIMENSIONS;i>0;--i)
                        {
                            const OutputType res = Squared(vect[i]);
                            xadd << res;
                        }
                    }
                };


            }

            //! \return |lhs|^2
            /**
             \param xadd perform additions
             \param lhs  lhs sequence
             */
            template <typename T, typename LHS> inline
            T Norm2(Cameo::Addition<T> &xadd, LHS &lhs)
            {
                typedef typename LHS::Type                                        InputType;
                typedef          Hub::Norm2<InputType,IsScalar<InputType>::Value> API;

                xadd.ldz();
                for(size_t i=lhs.size();i>0;--i)
                    API::Push(xadd,lhs[i]);
                return xadd.sum();
            }




        }
    }

}

#endif

