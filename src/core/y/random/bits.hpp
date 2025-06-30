//! \file

#ifndef Y_Random_Bits_Included
#define Y_Random_Bits_Included 1

#include "y/ability/serializable.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace Random
    {

        class Bits : public Identifiable
        {
        public:
            class               Metrics;
            typedef long double Real;

        protected:
            explicit Bits(const uint32_t highest32) noexcept;

        public:
            virtual ~Bits() noexcept;
            virtual uint32_t next32() noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Bits);
            Metrics * const metrics;
        };



    }
}

#endif

