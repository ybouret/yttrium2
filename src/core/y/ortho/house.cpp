
#include "y/ortho/house.hpp"

namespace Yttrium
{
    namespace Ortho
    {

        HouseInfo:: HouseInfo(const size_t dims) :
        metrics(dims),
        vecPool(metrics)
        {
        }

        
        HouseInfo:: ~HouseInfo() noexcept
        {
        }


        House:: House(const size_t dims) :
        HouseInfo(dims),
        Family(vecPool)
        {
        }

        House:: ~House() noexcept
        {
        }


    }

}
