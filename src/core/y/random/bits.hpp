//! \file

#ifndef Y_Random_Bits_Included
#define Y_Random_Bits_Included 1

#include "y/ability/serializable.hpp"
#include "y/ability/identifiable.hpp"

#include "y/type/traits.hpp"

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
            Real             real32() noexcept;
            uint64_t         fill64(const size_t nbit) noexcept;
            bool             choice() noexcept;

            template <typename T> inline T toR() noexcept { return static_cast<T>( real32() ); }
            template <typename T> inline T toU() noexcept
            {
                return static_cast<T>( fill64(sizeof(T)*8) );
            }

            template <typename T> inline T toS() noexcept
            {
                const T u = static_cast<T>( fill64(sizeof(T)*8-1) );
                return choice() ? -u : u;
            }




        private:
            Y_Disable_Copy_And_Assign(Bits);
            Metrics * const metrics;
        };



    }
}

#endif

