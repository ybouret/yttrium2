//! \file

#ifndef Y_MKL_Eigen_Included
#define Y_MKL_Eigen_Included 1

#include "y/container/matrix.hpp"

namespace Yttrium
{
    namespace MKL
    {
        struct Eigen
        {
            template <typename T>
            class Balance
            {
            public:
                explicit Balance();
                virtual ~Balance() noexcept;

                void operator()(Matrix<T> &a);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(Balance);
                Code * const code;
            };



        };
    }
}


#endif // !Y_MKL_Eigen_Included

