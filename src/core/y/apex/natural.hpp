
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/number.hpp"
#include "y/apex/types.hpp"
#include "y/apex/k/ops.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Random { class Bits; }

    namespace Apex
    {


        class Device;

        class Natural : public Number
        {
        public:
            static OpsMode Ops;
            static const char * const CallSign;

            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t);
            Y_OSTREAM_PROTO(Natural);

            Natural(Random::Bits &ran, const size_t bits);
            Natural(const TwoToThePowerOf_ &, const size_t n);


            virtual size_t serialize(OutputStream &) const;
            size_t    bits() const noexcept;
            Natural & xch(Natural &) noexcept;

        private:
            Device * const device;

        };

    }

    typedef Apex::Natural apn;
}

#endif
