
//! \file

#ifndef Y_Ink_Histogram_Included
#define Y_Ink_Histogram_Included 1

#include "y/ink/ops.hpp"

namespace Yttrium
{
    namespace Ink
    {
        class Histogram
        {
        public:
            typedef uint32_t    Type;
            static const size_t Bins = 256;

            explicit Histogram() noexcept;
            virtual ~Histogram() noexcept;

            Histogram & ldz() noexcept;
            Type &       operator[](const uint8_t) noexcept;
            const Type & operator[](const uint8_t) const noexcept;

            Histogram & operator+= (const Type * const arr) noexcept;


        private:
            Y_Disable_Copy_And_Assign(Histogram);
            Type bin[Bins];
        };
    }

}

#endif // !Y_Ink_Histogram_Included
