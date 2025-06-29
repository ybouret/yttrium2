
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/types.hpp"
#include "y/apex/number.hpp"
#include "y/apex/block/ops.hpp"
#include "y/mkl/two-to-the-power-of.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Model;

        class Natural : public Number
        {
        public:
            static OpsMode Ops;
            Natural();
            virtual ~Natural() noexcept;
            Natural(const Natural &);
            Natural & operator=(const Natural &);

            Natural(const natural_t);
            Natural & operator=(const natural_t) noexcept;

            Natural(const TwoToThePowerOf_ &, const size_t n);
            Y_OSTREAM_PROTO(Natural);

            std::ostream & printHex(std::ostream &) const;


            // addition
            Natural operator+() const; //!< \return duplicate


            // interface
            virtual size_t serialize(OutputStream &fp) const;
            
        private:
            Model * const code;
        };


    }

}

#endif

