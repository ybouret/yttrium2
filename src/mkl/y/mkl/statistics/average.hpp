//! \file

#ifndef Y_MKL_Statistics_Average_Included
#define Y_MKL_Statistics_Average_Included 1

#include "y/cameo/addition.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/static/moniker.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Statistics
        {

            template <typename T>
            class Average  : public Recyclable
            {
            public:
                typedef typename FCPU<T>::Type fcpu_t;
                Y_Args_Declare(T,Type);

                inline explicit Average() :
                Recyclable(),
                xadd(),
                nadd(0),
                zero()
                {}

                inline virtual ~Average() noexcept {}

                inline virtual size_t size() const noexcept { return nadd; }
                inline virtual void   free() noexcept { xadd.ldz(); nadd = 0; }

                inline Average & operator<<(ParamType args)
                {
                    xadd << args;
                    ++nadd;
                    return *this;
                }



            private:
                Y_Disable_Copy_And_Assign(Average);
                Cameo::Addition<T>       xadd;
                size_t                   nadd;
            public:
                const Static::Moniker<T> zero;

            };

        }

    }
}

#endif // !Y_MKL_Statistics_Average_Included
