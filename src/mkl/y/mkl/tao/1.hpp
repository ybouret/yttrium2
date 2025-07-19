
//! \file

#ifndef Y_MKL_Tao1_Included
#define Y_MKL_Tao1_Included 1

#include "y/cameo/addition.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {

            template <typename TARGET, typename SOURCE> inline
            void Load(TARGET &target, SOURCE &source)
            {
                assert(source.size()>=target.size());
                for(size_t i=target.size();i>0;--i)
                {
                    target[i] = source[i];
                }
            }

            template <typename T, typename LHS, typename RHS> inline
            T Dot(Cameo::Addition<T> &xadd, LHS &lhs, RHS &rhs)
            {
                assert( lhs.size() == rhs.size() );
                xadd.ldz();
                for(size_t i=lhs.size();i>0;--i)
                    xadd.addProd(lhs[i],rhs[i]);
                return xadd.sum();
            }


        }
    }

}

#endif

