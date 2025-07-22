
//! \file

#ifndef Y_MKL_LU_Included
#define Y_MKL_LU_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include "y/container/matrix.hpp"

namespace Yttrium
{
    namespace MKL
    {
        template <typename T>
        class LU : public Releasable
        {
        public:
            Y_Args_Declare(T,Type);
            typedef typename ScalarFor<T>::Type ScalarType;

            explicit LU(const size_t maxDim=0);
            virtual ~LU() noexcept;

            virtual void release() noexcept;
            bool build(Matrix<T> &a);
            T    det(const Matrix<T> &a); // determinant of a decomposed matrix
        
        private:
            class Code;
            Y_Disable_Copy_And_Assign(LU);
            void release_() noexcept;
            Code *code;
        };
    }

}


#endif

