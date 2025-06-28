
//! \file

#ifndef Y_Apex_Natural_Included
#define Y_Apex_Natural_Included 1

#include "y/apex/types.hpp"
#include "y/apex/number.hpp"
#include "y/apex/block/ops.hpp"

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
            
            // interface
            virtual size_t serialize(OutputStream &fp) const;
            
        private:
            Model * const code;
        };


    }

}

#endif

