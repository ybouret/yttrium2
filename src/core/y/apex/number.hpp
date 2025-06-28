

#ifndef Y_Apex_Number_Included
#define Y_Apex_Number_Included 1

#include "y/ability/serializable.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Number : public Serializable
        {
        protected:
            explicit Number() noexcept;

        public:
            virtual ~Number() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Number);
        };
    }

}

#endif

