
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1

#include "y/cameo/summator/vectorial.hpp"
#include "y/mkl/api/scalar.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        template <typename T>
        struct SummatorFor
        {
            static const bool IsScalar = MKL::IsScalar<T>::Value;
            typedef typename Pick<IsScalar, ScalarSummator<T>, VectorialSummator<T> >::Type Type;
        };

        //______________________________________________________________________
        //
        //
        //
        //! Addition with API based on type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Addition : public SummatorFor<T>::Type
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename SummatorFor<T>::Type SummatorType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            inline explicit Addition() : SummatorType()  {}

            //! setup with summator accepting initializer \param n capacity
            inline explicit Addition(const size_t n) : SummatorType(n) {}

            //! cleanup
            inline virtual ~Addition() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Addition); //!< discarding
        };

    }

}

#endif
