
//! \file

#ifndef Y_Apex_Ortho_House_Included
#define Y_Apex_Ortho_House_Included 1

#include "y/ortho/family.hpp"

namespace Yttrium
{
    namespace Ortho
    {

        class HouseInfo
        {
        public:
            explicit HouseInfo(const size_t dims);
            virtual ~HouseInfo() noexcept;

            const Metrics metrics;
            Vector::Pool  vecPool;

        private:
            Y_Disable_Copy_And_Assign(HouseInfo);
        };

        class House : public HouseInfo,  public Family
        {
        public:
            explicit House(const size_t dims);
            virtual ~House() noexcept;

        private:
            Y_Disable_Copy_And_Assign(House);
        };
    }

}

#endif

