
//! \file

#ifndef Y_Apex_Device_Included
#define Y_Apex_Device_Included 1

#include "y/apex/k/parcels.hpp"
#include "y/object.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/string.hpp"
#include "y/apex/k/ops.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace Apex
    {

        class Device : public Object, public Parcels
        {
        public:
            static const size_t   NumOps = Ops32_64+1;
            static const PlanType SmallPlan[NumOps];


            explicit Device(const size_t   userBlockSize,
                            const PlanType userBlockPlan);
            explicit Device(const CopyOf_ &,const uint64_t);
            Device(const Device &);
            virtual ~Device() noexcept;


            void   ld(const uint64_t) noexcept;
            void   shr() noexcept;
            String hex()                const;
            size_t srz(OutputStream &) const;
            void   com()  noexcept; //!< propagate bits

            const size_t   bits;  //!< current bits
            const size_t & bytes; //!< current bytes in Plan8
            const size_t & space; //!< in bytes
            
        private:
            Y_Disable_Assign(Device);
            void ld_(const uint64_t) noexcept;
            
        };


    }

}

#endif
