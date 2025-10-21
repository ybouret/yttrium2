//! \file

#ifndef Y_MKL_Statistics_Average_Included
#define Y_MKL_Statistics_Average_Included 1

#include "y/cameo/addition.hpp"
#include "y/mkl/api/fcpu.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Statistics
        {

            template <typename T>
            class Average 
            {
            public:
                typedef typename FCPU<T>::Type fcpu_t;

                inline explicit Average() {}
                inline virtual ~Average() noexcept {}

            private:
                Y_Disable_Copy_And_Assign(Average);
                Cameo::Addition<T> xadd;
            };

        }

    }
}

#endif // !Y_MKL_Statistics_Average_Included
